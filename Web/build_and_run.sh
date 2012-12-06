#!/bin/bash
export CHROOT="/var/chroot"

rm -rf "${CHROOT}/tmp/*"
set -e
ulimit -f 1000
[ -f main.cpp ] || { echo "Webserver could not find main.cpp. Exiting." 1>&2 ; exit 1; }
cp compile.sh main.cpp "${CHROOT}/tmp/"
chmod 755 "${CHROOT}/tmp/compile.sh"

# Run the chroot
#{ { sleep 5 && echo "Timeout!" && { pkill -9 -u sandbox >/dev/null 2>&1  ; } && exit 1 ; } & } && { trap "kill $! >/dev/null 2>&1" INT ERR EXIT; ./chroot.sh ; exit 0 ; }
./chroot.sh
