#!/bin/zsh
#
#   (c) FFRI Security, Inc., 2025 / Author: FFRI Security, Inc.
#

get_random_apple_app_with_provenance() {
    local apps=(/Applications/*.app)
    local apple_apps=()

    for app in "${apps[@]}"; do
        if [ -d "$app" ] && xattr -px com.apple.provenance "$app" &>/dev/null; then
            apple_apps+=("$app")
        fi
    done

    if [ ${#apple_apps[@]} -eq 0 ]; then
        return 0
    fi

    local random_index=$((RANDOM % ${#apple_apps[@]}))
    printf "%s" "${apple_apps[$random_index]}"
    return 0
}

get_app_provenance() {
    local app_path="$1"
    local provenance=""

    if [ -n "$app_path" ]; then
        provenance=$(xattr -px com.apple.provenance "$app_path" 2>/dev/null)
    fi

    printf "%s" "$provenance"
    return 0
}

make -C ./test copy || {
    echo "Error: Failed to execute 'make copy'" >&2
    exit 1
}

if [ $# -eq 1 ]; then
    if [ ! -d "$1" ] || [[ ! "$1" =~ \.app$ ]]; then
        echo "Error: Argument must be a valid application bundle" >&2
        exit 1
    fi
    
    app_bundle="$1"
else
    app_bundle=$(get_random_apple_app_with_provenance)
fi

base_provenance=$(get_app_provenance "$app_bundle")
if [ -z "$base_provenance" ]; then
    echo "Error: Failed to get base provenance value" >&2
    exit 1
fi

echo "Retrieved provenance value: $base_provenance"
echo "Source application bundle: $app_bundle"

echo "Setting provenance on executable files..."
for dir in ./test/exec{0,1,2}; do
    for exec_file in "$dir"/*; do
        if [ -x "$exec_file" ]; then
            xattr -wx com.apple.provenance "$base_provenance" "$exec_file" || {
                echo "Error: Failed to set provenance on $exec_file" >&2
                continue
            }
        fi
    done
done

echo "Testing that provenance attributes are set correctly..."

test_file0="/tmp/test0"
rm -f "$test_file0"
for exec_file in ./test/exec0/*; do
    if [ -x "$exec_file" ]; then
        "$exec_file" "$test_file0" || {
            echo "Error: Failed to execute $exec_file" >&2
            rm -f "$test_file0"
            continue
        }

        test_provenance=$(xattr -px com.apple.provenance "$test_file0" 2>/dev/null)
        if [ -z "$test_provenance" ]; then
            echo "Warning: Extended attribute 'com.apple.provenance' was not set by $exec_file"
        elif [ "$test_provenance" != "$base_provenance" ]; then
            echo "Warning: Provenance value mismatch for $exec_file"
            echo "Expected: $base_provenance"
            echo "Got: $test_provenance"
        else
            echo "Provenance values match for $exec_file"
        fi
        rm -f "$test_file0"
    fi
done

test_file1="/tmp/test1"
rm -f "$test_file1"
for exec_file in ./test/exec1/*; do
    if [ -x "$exec_file" ]; then
        : > "$test_file1" || {
            echo "Error: Failed to create test file" >&2
            continue
        }

        if [ "$(basename "$exec_file")" = "deleteextattr" ]; then
            xattr -w test "test" "$test_file1" || {
                echo "Warning: Failed to set 'test' extended attribute on $test_file1" >&2
            }
        fi
        
        "$exec_file" "$test_file1" || {
            echo "Error: Failed to execute $exec_file" >&2
            rm -f "$test_file1"
            continue
        }
        
        test_provenance=$(xattr -px com.apple.provenance "$test_file1" 2>/dev/null)
        if [ -z "$test_provenance" ]; then
            echo "Warning: Extended attribute 'com.apple.provenance' was not set by $exec_file"
        elif [ "$test_provenance" != "$base_provenance" ]; then
            echo "Warning: Provenance value mismatch for $exec_file"
            echo "Expected: $base_provenance"
            echo "Got: $test_provenance"
        else
            echo "Provenance values match for $exec_file"
        fi
        
        chflags nouappnd "$test_file1" || {
            echo "Warning: Failed to clear file flags on $test_file1" >&2
        }
        rm -f "$test_file1"
    fi
done

test_file2_0="/tmp/test2_0"
test_file2_1="/tmp/test2_1"
rm -f "$test_file2_0" "$test_file2_1"
for exec_file in ./test/exec2/*; do
    if [ -x "$exec_file" ]; then
        : > "$test_file2_0" || {
            echo "Error: Failed to create test file $test_file2_0" >&2
            continue
        }

        if [ "$(basename "$exec_file")" = "swap" ]; then
            echo "This is test file 2_1" > "$test_file2_1" || {
                echo "Error: Failed to create test file $test_file2_1" >&2
                rm -f "$test_file2_0"
                continue
            }
            echo "This is test file 2_0" > "$test_file2_0" || {
                echo "Error: Failed to create test file $test_file2_0" >&2
                rm -f "$test_file2_1"
                continue
            }
        fi
        
        "$exec_file" "$test_file2_0" "$test_file2_1" || {
            echo "Error: Failed to execute $exec_file" >&2
            rm -f "$test_file2_0" "$test_file2_1"
            continue
        }
        
        for test_file in "$test_file2_0" "$test_file2_1"; do
            if [ -f "$test_file" ]; then
                test_provenance=$(xattr -px com.apple.provenance "$test_file" 2>/dev/null)
                if [ -z "$test_provenance" ]; then
                    echo "Warning: Extended attribute 'com.apple.provenance' was not set by $exec_file on $test_file"
                elif [ "$test_provenance" != "$base_provenance" ]; then
                    echo "Warning: Provenance value mismatch for $exec_file on $test_file"
                    echo "Expected: $base_provenance"
                    echo "Got: $test_provenance"
                else
                    echo "Provenance values match for $exec_file on $test_file"
                fi
            fi
        done
        
        rm -f "$test_file2_0" "$test_file2_1"
    fi
done


echo "Test completed successfully"
