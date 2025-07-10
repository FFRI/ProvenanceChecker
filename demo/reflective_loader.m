/*
 *  (c) FFRI Security, Inc., 2025 / Author: FFRI Security, Inc.
 */
#import <Foundation/Foundation.h>
#import <mach-o/dyld.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide a dylib path as argument\n");
        return EXIT_FAILURE;
    }

    NSError *error = nil;
    NSData *dylibData = [NSData dataWithContentsOfFile:@(argv[1]) 
                                              options:0 
                                                error:&error];
    if (!dylibData) {
        fprintf(stderr, "Error: Failed to read dylib file: %s\n", 
                [[error localizedDescription] UTF8String]);
        return EXIT_FAILURE;
    }

    NSMutableData *mutableDylibData = [dylibData mutableCopy];
    uint32_t *header = (uint32_t *)mutableDylibData.mutableBytes;
    header[3] = MH_BUNDLE;
    dylibData = mutableDylibData;

    NSObjectFileImage fileImage;
    NSObjectFileImageReturnCode returnCode = 
        NSCreateObjectFileImageFromMemory((void *)dylibData.bytes,
                                        dylibData.length,
                                        &fileImage);
                                        
    if (returnCode != NSObjectFileImageSuccess) {
        fprintf(stderr, "Error: Failed to create object file image\n");
        return EXIT_FAILURE;
    }

    NSModule module = NSLinkModule(fileImage, argv[1], 
                                 NSLINKMODULE_OPTION_PRIVATE | 
                                 NSLINKMODULE_OPTION_BINDNOW);
    
    if (!module) {
        fprintf(stderr, "Error: Failed to link module\n");
        NSDestroyObjectFileImage(fileImage);
        return EXIT_FAILURE;
    }

    printf("Successfully loaded dylib: %s\n", argv[1]);

    NSDestroyObjectFileImage(fileImage);
    
    return EXIT_SUCCESS;
}
