# Provenance Checker

## What is this?

This tool helps you verify which file operations performed by provenance-sandboxed applications result in the `com.apple.provenance` attribute being set. Currently, we have confirmed that the `com.apple.provenance` attribute is set for the following operations:

- create
- deleteextattr
- open (with write mode)
- setacl
- setattrlist
- setextattr
- setflags
- setmode
- setowner
- setutimes
- truncate
- link
- rename

## How to use

```
./check.sh
# or use a specific app (which should have the com.apple.provenance attribute)
./check.sh /Applications/test.app
```

## Example

```
user@users-Virtual-Machine ProvenanceChecker % ./check.sh /Applications/Google\ Chrome.app 
mkdir -p ./exec0 ./exec1 ./exec2
cp create ./exec0/;
cp deleteextattr ./exec1/; cp open_read ./exec1/; cp open_write ./exec1/; cp setacl ./exec1/; cp setattrlist ./exec1/; cp setextattr ./exec1/; cp setflags ./exec1/; cp setmode ./exec1/; cp setowner ./exec1/; cp setutimes ./exec1/; cp truncate ./exec1/;
cp rename ./exec2/; cp swap ./exec2/; cp link ./exec2/;
Retrieved provenance value: 01 02 00 50 4A 22 FA 77 3C 5F 21 
Source application bundle: /Applications/Google Chrome.app
Setting provenance on executable files...
Testing provenance attributes are set correctly...
Provenance values match for ./test/exec0/create
Provenance values match for ./test/exec1/deleteextattr
Warning: Extended attribute 'com.apple.provenance' was not set by ./test/exec1/open_read
Provenance values match for ./test/exec1/open_write
Provenance values match for ./test/exec1/setacl
Provenance values match for ./test/exec1/setattrlist
Provenance values match for ./test/exec1/setextattr
Provenance values match for ./test/exec1/setflags
Provenance values match for ./test/exec1/setmode
Provenance values match for ./test/exec1/setowner
Provenance values match for ./test/exec1/setutimes
Provenance values match for ./test/exec1/truncate
Provenance values match for ./test/exec2/link on /tmp/test2_0
Provenance values match for ./test/exec2/link on /tmp/test2_1
Provenance values match for ./test/exec2/rename on /tmp/test2_1
Warning: Extended attribute 'com.apple.provenance' was not set by ./test/exec2/swap on /tmp/test2_0
Warning: Extended attribute 'com.apple.provenance' was not set by ./test/exec2/swap on /tmp/test2_1
Test completed successfully
user@users-Virtual-Machine ProvenanceChecker % sudo sqlite3 /var/db/SystemPolicyConfiguration/ExecPolicy
SQLite version 3.43.2 2023-10-10 13:08:14
Enter ".help" for usage hints.
sqlite> .dump provenance_tracking
PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE provenance_tracking (  pk INTEGER PRIMARY KEY,  url TEXT NOT NULL,  bundle_id TEXT,  cdhash TEXT,  team_identifier TEXT,  signing_identifier TEXT,  flags INTEGER,  timestamp INTEGER NOT NULL,  link_pk INTEGER);
INSERT INTO provenance_tracking VALUES(-8705005594656364080,'/Users/user/ProvenanceChecker/test/exec2/swap','NOT_A_BUNDLE','8d3ddb78a7d3efb278cf814f9181f8b9be089e88',NULL,'swap',2,1736766299,2404707212034460240);
INSERT INTO provenance_tracking VALUES(-8387905036243883148,'/Users/user/ProvenanceChecker/test/exec1/setattrlist','NOT_A_BUNDLE','799f0564d350c92de86f4625f1084e2fb47c2966',NULL,'setattrlist',2,1736766298,2404707212034460240);
INSERT INTO provenance_tracking VALUES(-7198059946396010082,'/Users/user/ProvenanceChecker/test/exec1/open_write','NOT_A_BUNDLE','b2d88039584ab046ece5f1a70d9d8078da5862b3',NULL,'open_write',2,1736766297,2404707212034460240);
INSERT INTO provenance_tracking VALUES(-6473314178968461656,'/Users/user/ProvenanceChecker/test/exec1/setmode','NOT_A_BUNDLE','945c12973a9266d95106c861c710b173d6898d7b',NULL,'setmode',2,1736766298,2404707212034460240);
INSERT INTO provenance_tracking VALUES(-6152992529727447362,'/Users/user/ProvenanceChecker/test/exec1/deleteextattr','NOT_A_BUNDLE','31ef6d21ed2cf911d4fbd4722e82cfa8bbb83e73',NULL,'deleteextattr',2,1736766297,2404707212034460240);
INSERT INTO provenance_tracking VALUES(-5863915026961211569,'/Users/user/ProvenanceChecker/test/exec1/truncate','NOT_A_BUNDLE','4fa5d22d8decad2e57dd4c3db0638427ca0994bd',NULL,'truncate',2,1736766299,2404707212034460240);
INSERT INTO provenance_tracking VALUES(-2737531160156372246,'/Users/user/ProvenanceChecker/test/exec1/open_read','NOT_A_BUNDLE','c8c05eb95c1f953481481fa93326cf77c7b7fe04',NULL,'open_read',2,1736766297,2404707212034460240);
INSERT INTO provenance_tracking VALUES(-1391420977783423786,'/Users/user/ProvenanceChecker/test/exec1/setacl','NOT_A_BUNDLE','8f1e002d955c87c296d57e021a724c8de86c50d0',NULL,'setacl',2,1736766297,2404707212034460240);
INSERT INTO provenance_tracking VALUES(-1104642703188079920,'/Users/user/ProvenanceChecker/test/exec1/setutimes','NOT_A_BUNDLE','0c5e1f909d15036d469cfed09a419ebf6e80106f',NULL,'setutimes',2,1736766299,2404707212034460240);
INSERT INTO provenance_tracking VALUES(-849214683069893280,'/Users/user/ProvenanceChecker/test/exec2/rename','NOT_A_BUNDLE','9713914de96d2701a7142a38386caaa586464476',NULL,'rename',2,1736766299,2404707212034460240);
INSERT INTO provenance_tracking VALUES(-320004898073574477,'/Users/user/ProvenanceChecker/test/exec1/setflags','NOT_A_BUNDLE','d67b46a342df13757fd0d5bfa2d149364abae7e3',NULL,'setflags',2,1736766298,2404707212034460240);
INSERT INTO provenance_tracking VALUES(1113012025703127136,'/Users/user/ProvenanceChecker/test/exec1/setowner','NOT_A_BUNDLE','81943bb0003ccd4e3a789e1d969614e89883881c',NULL,'setowner',2,1736766298,2404707212034460240);
INSERT INTO provenance_tracking VALUES(1248162858123011501,'/Users/user/ProvenanceChecker/test/exec2/link','NOT_A_BUNDLE','ab1aeb70212d8a2561e738d5e7e7e417169bbfce',NULL,'link',2,1736766299,2404707212034460240);
INSERT INTO provenance_tracking VALUES(2404707212034460240,'/Applications/Google Chrome.app','com.google.Chrome','8137beefb3eabec723e516061e6611ecca079057','EQHXZ8M8AV','com.google.Chrome',2,1736581744,0);
INSERT INTO provenance_tracking VALUES(6540580282830126991,'/Users/user/ProvenanceChecker/test/exec1/setextattr','NOT_A_BUNDLE','b213267bc9755d6218e0cb3f783d92aeb2213b8b',NULL,'setextattr',2,1736766298,2404707212034460240);
INSERT INTO provenance_tracking VALUES(8052744398924416575,'/Users/user/ProvenanceChecker/test/exec0/create','NOT_A_BUNDLE','4818e3c774c0e86d86b0f023935ffab870a32947',NULL,'create',2,1736766297,2404707212034460240);
COMMIT;
```

## Author

Koh M. Nakagawa (@tsunek0h) &copy; FFRI Security, Inc. 2025

## License

[Apache version 2.0](LICENSE)
