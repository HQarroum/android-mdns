LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CLASS_PATH := $(LOCAL_PATH)/../../../build/intermediates/classes/debug

LOCAL_MODULE := jdns_sd

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH) \
	$(LOCAL_PATH)/mDNSShared \
	$(LOCAL_PATH)/mDNSPosix \
	$(LOCAL_PATH)/mDNSCore 

LOCAL_CFLAGS :=  \
	-DMDNS_DEBUGMSGS=0 \
	-DTARGET_OS_ANDROID \
	-DUSES_BROADCAST_AND_MULTICAST \
	-DNOT_HAVE_SA_LEN -DUSES_NETLINK

LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog

GENERATE_CLASSES := $(shell javah -force -classpath $(LOCAL_CLASS_PATH) -o $(LOCAL_PATH)/DNSSD.java.h \
	com.apple.dnssd.AppleDNSSD \
	com.apple.dnssd.AppleBrowser \
	com.apple.dnssd.AppleResolver \
	com.apple.dnssd.AppleRegistration \
	com.apple.dnssd.AppleQuery \
	com.apple.dnssd.AppleDomainEnum \
	com.apple.dnssd.AppleService \
	com.apple.dnssd.AppleDNSRecord \
	com.apple.dnssd.DNSSDEmbedded \
	)

$(GENERATE_CLASSES)

LOCAL_SRC_FILES := \
    mDNSPosix/mDNSPosix.c \
    mDNSPosix/mDNSUNP.c \
    mDNSPosix/PosixDaemon.c \
    mDNSShared/mDNSDebug.c \
    mDNSShared/GenLinkedList.c \
    mDNSCore/DNSDigest.c \
    mDNSCore/uDNS.c \
    mDNSCore/DNSCommon.c \
    mDNSShared/PlatformCommon.c \
    mDNSCore/mDNS.c \
    mDNSShared/dnssd_clientlib.c \
    mDNSShared/dnssd_clientshim.c \
    mDNSShared/Java/JNISupport.c \
    mDNSShared/dnssd_ipc.c \
    mDNSShared/uds_daemon.c \
    mDNSCore/mDNSEmbedded.c

include $(BUILD_SHARED_LIBRARY)

