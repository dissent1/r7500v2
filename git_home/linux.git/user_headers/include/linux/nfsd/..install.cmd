cmd_/home/roger.luo/auto-gpl/tmp/linux/linux-3.4.103/user_headers/include/linux/nfsd/.install := perl /home/roger.luo/auto-gpl/tmp/linux/linux-3.4.103/sourcecode/scripts/headers_install.pl /home/roger.luo/auto-gpl/tmp/linux/linux-3.4.103/sourcecode/include/linux/nfsd /home/roger.luo/auto-gpl/tmp/linux/linux-3.4.103/user_headers/include/linux/nfsd arm cld.h debug.h export.h nfsfh.h stats.h; perl /home/roger.luo/auto-gpl/tmp/linux/linux-3.4.103/sourcecode/scripts/headers_install.pl /home/roger.luo/auto-gpl/tmp/linux/linux-3.4.103/include/linux/nfsd /home/roger.luo/auto-gpl/tmp/linux/linux-3.4.103/user_headers/include/linux/nfsd arm ; perl /home/roger.luo/auto-gpl/tmp/linux/linux-3.4.103/sourcecode/scripts/headers_install.pl /home/roger.luo/auto-gpl/tmp/linux/linux-3.4.103/include/generated/linux/nfsd /home/roger.luo/auto-gpl/tmp/linux/linux-3.4.103/user_headers/include/linux/nfsd arm ; for F in ; do echo "\#include <asm-generic/$$F>" > /home/roger.luo/auto-gpl/tmp/linux/linux-3.4.103/user_headers/include/linux/nfsd/$$F; done; touch /home/roger.luo/auto-gpl/tmp/linux/linux-3.4.103/user_headers/include/linux/nfsd/.install
