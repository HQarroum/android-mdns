![Logo](http://techraptor.net/wp-content/uploads/2014/05/Apple-Bonjour-650x330.png)

## Android mDNS

The Apple mDNS stack built and packaged for Android.

Current version: **98.0.0**

Lead Maintainer: [Halim Qarroum](mailto:hqm.post@gmail.com)

### Description

Bonjour is Apple's implementation of Zero-configuration networking (Zeroconf), a group of technologies that includes service discovery, address assignment, and hostname resolution. Bonjour locates devices such as printers, other computers, and the services that those devices offer on a local network using multicast Domain Name System (mDNS) service records.

The software comes built-in with Apple's OS X and iOS operating systems. Bonjour can also be installed onto computers running Microsoft Windows. Bonjour components may also be included within other software such as iTunes and Safari.

To be used in an Android environment, the Apple's mDNS stack requires a bit of adjustement, and certain wrapping layers are required to ensure that it can properly be used withing an application. It is the purpose of this project to provide a Gradle-based project allowing you to embed the stack into any app using a simple API.

### Use-cases

This mDNS stack can mostly be used for device and service discovery purposes. It is for instance possible to  discover devices embedding an mDNS stack (such as the vast majority of Apple's devices), but also to discover the services associated with this device (e.g a webservice returning a webpage hosted by a printer).

### To-dos

This application is subject to heavy changes in order to provide clearer and more usable wrapping mechanisms. It is also scheduled to push the resulting artifact to a Maven repository in order for this project to be more easily integrable with Gradle's dependency system.
