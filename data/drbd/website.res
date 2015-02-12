resource website {
 meta-disk internal;
 device  /dev/drbd1;
 syncer {
  verify-alg sha1;
 }

