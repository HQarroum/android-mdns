#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>

#include "mDNSEmbeddedAPI.h"
#include "mDNSPosix.h"

mDNS mDNSStorage;
static mDNS_PlatformSupport PlatformStorage;
#define RR_CACHE_SIZE 500
static CacheEntity gRRCache[RR_CACHE_SIZE];
int stopNow = 0;
static int state = 0;

mDNSexport int embedded_mDNSInit() {
  mStatus status;
  status = mDNS_Init(&mDNSStorage, &PlatformStorage, gRRCache, RR_CACHE_SIZE,
		     mDNS_Init_AdvertiseLocalAddresses,
		     mDNS_Init_NoInitCallback, mDNS_Init_NoInitCallbackContext);
  return status;
}

mDNSexport void embedded_mDNSExit() {
  stopNow = 1;
}

mDNSexport void embedded_mDNSLoop() {
  mDNS* m = &mDNSStorage;
  stopNow = 0;
  state   = 1;
  
  while (!stopNow) {
    int nfds = 0;
    fd_set readfds;
    struct timeval timeout;
    int result;

    FD_ZERO(&readfds);
    timeout.tv_sec = 0x1;
    timeout.tv_usec = 0;
    mDNSPosixGetFDSet(m, &nfds, &readfds, &timeout);
    result = select(nfds, &readfds, NULL, NULL, &timeout);

    if (result < 0) {
      if (errno != EINTR)
	stopNow = 1;
    } else {
      mDNSPosixProcessFDSet(m, &readfds);
    }
    sigset_t signals;
    mDNSBool gotSomething;
    mDNSPosixRunEventLoopOnce(m, &timeout, &signals, &gotSomething);
  }
  state = 0;
  mDNS_Close(&mDNSStorage);
}
