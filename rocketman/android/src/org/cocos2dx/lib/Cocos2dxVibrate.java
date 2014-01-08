package org.cocos2dx.lib;

import android.content.Context;
import android.os.Vibrator;

public class Cocos2dxVibrate {
	
	private Context mContext;

	public Cocos2dxVibrate(Context context) {
		mContext = context;
	}
	
	public void vibrate() {
		Vibrator v = (Vibrator)mContext.getSystemService(Context.VIBRATOR_SERVICE);
		int dash = 500;
		long[] pattern = {0, dash};		    
		v.vibrate(pattern, -1);
	}
}
