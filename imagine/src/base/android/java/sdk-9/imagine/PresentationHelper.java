/*  This file is part of Imagine.

	Imagine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Imagine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Imagine.  If not, see <http://www.gnu.org/licenses/> */

package com.imagine;

import android.app.*;
import android.content.*;
import android.os.*;
import android.util.*;
import android.view.*;
import android.hardware.display.*;

import android.graphics.*;
import android.graphics.drawable.*;

final class PresentationHelper extends Presentation
	implements DialogInterface.OnDismissListener, SurfaceHolder.Callback2
{
	private static final String logTag = "Presentation";
	private ContentView contentView;
	private native void onSurfaceCreated(long windowAddr, Surface surface);
	private native void onSurfaceRedrawNeeded(long windowAddr);
	private native void onSurfaceDestroyed(long windowAddr);
	
	PresentationHelper(Activity context, Display display, long windowAddr)
	{
		super(context, display);
		setOnDismissListener(this);
		contentView = new ContentView(context, windowAddr);
	}
	
	@Override protected void onCreate(Bundle savedInstanceState)
	{
		//Log.i(logTag, "onCreate");
		getWindow().takeSurface(this);
		setContentView(contentView);
	}
	
	// called by the native code if it deinits the window
	public void deinit()
	{
		contentView.windowAddr = 0;
		dismiss();
	}
	
	@Override public void onDismiss(DialogInterface dialog)
	{
		//Log.i(logTag, "presentation dismissed");
		if(contentView.windowAddr != 0)
		{
			// TODO: need to call native code and deinit the window
		}
	}
	
	public void surfaceCreated(SurfaceHolder holder)
	{
		//Log.i(logTag, "surfaceCreated");
		if(contentView.windowAddr != 0)
			onSurfaceCreated(contentView.windowAddr, holder.getSurface());
	}
	
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
	{
		//Log.i(logTag, "surfaceChanged");
	}
	
	public void surfaceRedrawNeeded(SurfaceHolder holder)
	{
		//Log.i(logTag, "surfaceRedrawNeeded");
		if(contentView.windowAddr != 0)
			onSurfaceRedrawNeeded(contentView.windowAddr);
	}
	
	public void surfaceDestroyed(SurfaceHolder holder)
	{
		//Log.i(logTag, "surfaceDestroyed");
		if(contentView.windowAddr != 0)
			onSurfaceDestroyed(contentView.windowAddr);
	}
}
