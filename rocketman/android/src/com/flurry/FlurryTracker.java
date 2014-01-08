package com.flurry;

import java.util.HashMap;
import java.util.Map;

import android.app.Activity;
import android.text.Html.TagHandler;
import android.util.Log;

import com.flurry.android.FlurryAgent;

public class FlurryTracker {

	public static void startSession(Activity activity) {
		FlurryAgent.onStartSession(activity, "J1GFL1TQ2MGNAQ2I62H3");
	}

	public static void endSession(Activity activity) {
		FlurryAgent.onEndSession(activity);
	}
	
	public static void logEvent(String name, Map<String, String> params) {
		FlurryAgent.logEvent(name, params);
	}
}
