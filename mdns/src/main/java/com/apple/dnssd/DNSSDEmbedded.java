package com.apple.dnssd;

import java.util.HashSet;
import java.util.Set;
import android.util.Log;

public class DNSSDEmbedded {

	public static Set<Listener> listeners = new HashSet<>();

	public static void init(Listener listener) {
		listeners.add(listener);
		init();
	}

	public static void init() {
		DNSSD.getInstance();
		new Thread() {
			public void run() {
				int ret = Init();
				if (ret != 0) {
					notifyOnError();
					return;
				}
				notifyOnStart();
				Loop();
				notifyOnEnd();
			}
		}.start();
	}

	public static void exit() {
		DNSSD.getInstance();
		Exit();
	}

	private static void notifyOnStart() {
		for (final Listener listener : listeners) {
			new Thread() {
				public void run() {
					listener.onStart();
				}
			}.start();
		}
	}

	private static void notifyOnEnd() {
		for (final Listener listener : listeners) {
			new Thread() {
				public void run() {
					listener.onEnd();
				}
			}.start();
		}
	}

	private static void notifyOnError() {
		for (final Listener listener : listeners) {
			new Thread() {
				public void run() {
					listener.onError();
				}
			}.start();
		}
	}

	protected static native int Init();

	protected static native void Loop();

	protected static native void Exit();

	public interface Listener {

		void onStart();

		void onEnd();

		void onError();
	}
}
