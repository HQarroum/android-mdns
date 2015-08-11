#ifndef _MDNSEMBEDDED_H_
#define _MDNSEMBEDDED_H_
#ifdef __cplusplus
extern "C" {
#endif
  int embedded_mDNSInit();
  void embedded_mDNSLoop();
  void embedded_mDNSExit();
#ifdef __cplusplus
}
#endif
#endif //_MDNSEMBEDDED_H_
