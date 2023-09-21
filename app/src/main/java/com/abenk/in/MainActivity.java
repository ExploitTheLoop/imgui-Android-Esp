package com.abenk.in;
import android.app.Activity;
import android.content.Context;
import android.graphics.PixelFormat;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.view.Gravity;
import android.view.MotionEvent;
import android.graphics.*;
import android.os.*;
import android.view.*;
import android.view.Window;
import android.view.WindowManager;

import java.io.InputStream;

import android.provider.Settings;
import android.widget.Toast;
import android.content.Intent;
import android.net.Uri;
import java.io.IOException;
import java.io.File;
import android.util.Log;

import java.io.FileOutputStream;

import android.content.pm.PackageManager;
import android.icu.util.Calendar;
import android.icu.text.SimpleDateFormat;

public class MainActivity extends Activity {
	int  屏宽,屏高;
	int Game = 1;
	int RootMode,GameBit;
	boolean HaveGame;
    static{
        System.loadLibrary("ayan");
    }

    public static native void getReady();
    private static MainActivity Instance;
	private WindowManager manager;

	private WindowManager.LayoutParams vParams;

	private View vTouch;
    public WindowManager windowManager,xfqManager;
	private WindowManager 绘制窗口;
    
    public static void 执行功能(String shell) {
        String s = shell;

        try {
            Runtime.getRuntime().exec(s, null, null);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
	
    public static boolean 写出资源文件(Context context, String outPath, String fileName) {
        File file = new File(outPath);
        if (!file.exists()) {
            if (!file.mkdirs()) {
                Log.e("--Method--", "copyAssetsSingleFile: cannot create directory.");
                return false;
            }
        }
        try {
            InputStream inputStream = context.getAssets().open(fileName);
            File outFile = new File(file, fileName);
            FileOutputStream fileOutputStream = new FileOutputStream(outFile);           
            byte[] buffer = new byte[1024];
            int byteRead;
            while (-1 != (byteRead = inputStream.read(buffer))) {
                fileOutputStream.write(buffer, 0, byteRead);
            }
            inputStream.close();
            fileOutputStream.flush();
            fileOutputStream.close();
            return true;
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }
	
	
	
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (!Settings.canDrawOverlays(this)) {
            Toast.makeText(this, "请授权应用悬浮窗权限", Toast.LENGTH_LONG).show();
            startActivityForResult(new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION, Uri.parse("package:" + getPackageName())), 0);
        }
		

		
		//Helo(this);
		
		loadAssets();
		
		
		
		写出资源文件(this,getFilesDir() + "/assets", "rayan");
		
        执行功能("chmod -R 777 " + getFilesDir() + "/assets");
		
        try {//申请root权限
            Runtime.getRuntime().exec("su", null, null);
        } catch (IOException e) {}   
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        windowManager = (WindowManager) getSystemService(Context.WINDOW_SERVICE);
        WindowManager 窗口=(WindowManager)getSystemService(Context.WINDOW_SERVICE);
        assert 窗口 != null;
		if (Build.VERSION.SDK_INT >= 21) {
			getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_LAYOUT_STABLE | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN);
		}
        
        setContentView(R.layout.activity_main);

		changeStatusBarColor();
		//透明状态栏和导航栏
		if (Build.VERSION.SDK_INT >= 19) {
			//透明状态栏
			this.getWindow().addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
			this.getWindow().addFlags(WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN);
			this.getWindow().addFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS);
			//透明导航栏
			this.getWindow().addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION);
		}
		if (Build.VERSION.SDK_INT >= 19) {
			this.getWindow().addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
		}
	}
    private boolean MvAssets(String outPath, String fileName)
	{
		File file = new File(outPath);
		if (!file.exists())
		{
			if (!file.mkdirs())
			{
				Log.e("--Method--", "copyAssetsSingleFile: cannot create directory.");
				return false;
			}
		}
		try
		{
			InputStream inputStream = getAssets().open(fileName);
			File outFile = new File(file, fileName);
			FileOutputStream fileOutputStream = new FileOutputStream(outFile);
			byte[] buffer = new byte[1024];
			int byteRead;
			while (-1 != (byteRead = inputStream.read(buffer)))
			{
				fileOutputStream.write(buffer, 0, byteRead);
			}
			inputStream.close();
			fileOutputStream.flush();
			fileOutputStream.close();
			return true;
		}
		catch (IOException e)
		{
			e.printStackTrace();
			return false;
		}
	}
	
	
	
	public void loadAssets()
	{
		
	MvAssets(getFilesDir()+"/","rayan");
		
		String filepath =Environment.getExternalStorageDirectory()+"/Android/data/.tyb";
		FileOutputStream fos = null;
		
		}
   public void onClick(View v) {
	   
	   if (RootMode != 0 && Game != 0 && GameBit != 0){
		   
		   if (Game == 1 && 打开应用(this,"com.tencent.ig")){
			   HaveGame = true;
		   } 
		   else if (Game == 2 && 打开应用(this,"com.pubg.krmobile")){
			   HaveGame = true;
		   } else if (Game == 3 && 打开应用(this,"com.rekoo.pubgm")){
			   HaveGame = true;
		   } else if (Game == 4 && 打开应用(this,"com.vng.pubgmobile")){
			   HaveGame = true;
		   } else if (Game == 5 && 打开应用(this,"com.pubg.imobile")){
			   HaveGame = true;
		   } 
		
		   if (HaveGame)
		   {
		   绘制窗口 = (WindowManager)getSystemService(Context.WINDOW_SERVICE);
		   //双悬浮方案，解决触摸问题
		   manager = (WindowManager) getApplicationContext().getSystemService(Context.WINDOW_SERVICE);
		   vParams = getAttributes(false);
		   WindowManager.LayoutParams wParams = getAttributes(true);
		   GLES3JNIView display = new GLES3JNIView(this);
		   vTouch = new View(this);
		   manager.addView(vTouch, vParams);
		   manager.addView(display, wParams);

		   GLES3JNIView.Mode(Game, RootMode,GameBit);

		   //获取悬浮窗触摸
		   vTouch.setOnTouchListener(new View.OnTouchListener() {
				   @Override
				   public boolean onTouch(View v, MotionEvent event) {
					   int action = event.getAction();
					   switch (action) {
						   case MotionEvent.ACTION_MOVE:
						   case MotionEvent.ACTION_DOWN:
						   case MotionEvent.ACTION_UP:
							   GLES3JNIView.MotionEventClick(action != MotionEvent.ACTION_UP, event.getRawX(), event.getRawY());
							   break;
						   default:
							   break;
					   }
					   return false;
				   }
			   });
			   
			   
   
			   
   
			   
		   final Handler handler = new Handler();
		   handler.postDelayed(new Runnable() {
				   @Override
				   public void run() {
					   try {
						   String rect[] = GLES3JNIView.getWindowRect().split("\\|");
						   vParams.x = Integer.parseInt(rect[0]);
						   vParams.y = Integer.parseInt(rect[1]);
						   vParams.width = Integer.parseInt(rect[2]);
						   vParams.height = Integer.parseInt(rect[3]);
						   manager.updateViewLayout(vTouch, vParams);
					   } catch (Exception e) {
					   }
					   handler.postDelayed(this, 20);
				   }
			   }, 20);
		   new Handler().postDelayed(new Runnable(){
				   @Override
				   public void run(){
					   if (RootMode == 64)
					   {
					       执行功能("su -c " + getFilesDir() + "/assets/rayan");
						//   执行功能("su -c " + getFilesDir() + "/assets/base 20");
						 //  startFloating();
					   }
					   else if (RootMode == 128)
					   {
						   执行功能("" + getFilesDir() + "/assets/rayan");
						// 执行功能("" + getFilesDir() + "/assets/base 20");
					   }
					   Start();
				   }
			   },6000);
		   
		   }
    } else {
		Toast.makeText(this, "你未选择以上模式", Toast.LENGTH_LONG).show();
	}
	}

    public  void Start() {
        if (Instance == null) {

            Thread t1=new Thread(new Runnable() {
                    @Override
                    public void run() {
                        getReady();
                    }
                });
            t1.start();
            Thread t2=new Thread(new Runnable() {
                    @Override
                    public void run() {
                        try {
                            Thread.sleep(200);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        //  Tool.runExecutable(FloatingModMenuService.this, "/assets/Son_non_fish", 1);
                    }
                });
            t2.start();
        }
    }
	/*
	
	private void startFloating(){

        {
            startService(new Intent(this, FloatingActivity.class));

        }
	}

    private void stopFloating(){
		stopService(new Intent(this, FloatingActivity.class));
		//stopService(new Intent(this, FloatingActivity2.class));

	}*/
	
	public static boolean 打开应用(Context context, String 包名) {
		PackageManager packageManager=context.getPackageManager();
		try {
		//	context.startActivity(packageManager.getLaunchIntentForPackage(包名));
			return true;
		} catch (Exception e) {
			Toast.makeText(context,"启动 " + 包名 + " 时失败", Toast.LENGTH_LONG).show();
			return false;
		}
	}

	private void changeStatusBarColor() {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
			Window window = getWindow();
			window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
			window.setStatusBarColor(Color.TRANSPARENT);
		}
	}
	private WindowManager.LayoutParams getAttributes(boolean isWindow) {
        WindowManager.LayoutParams params = new WindowManager.LayoutParams();
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            params.type = WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY;
        } else {
            params.type = WindowManager.LayoutParams.TYPE_PHONE;
        }
        params.flags = WindowManager.LayoutParams.FLAG_FULLSCREEN | WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS | WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION | WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;

        if (isWindow) {
            params.flags |= WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL | WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE;
        }
        params.format = PixelFormat.RGBA_8888;            // 设置图片格式，效果为背景透明
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            params.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
        }
        params.gravity = Gravity.LEFT | Gravity.TOP;        // 调整悬浮窗显示的停靠位置为左侧置顶
        params.x = params.y = 0;
        params.width = params.height = isWindow ? WindowManager.LayoutParams.MATCH_PARENT : 0;
        return params;
    }
	
	/*public boolean joinQQGroup(String key) {
		Intent intent = new Intent();
		intent.setData(Uri.parse("mqqopensdkapi://bizAgent/qm/qr?url=http%3A%2F%2Fqm.qq.com%2Fcgi-bin%2Fqm%2Fqr%3Ffrom%3Dapp%26p%3Dandroid%26jump_from%3Dwebapi%26k%3D" + key));
		// 此Flag可根据具体产品需要自定义，如设置，则在加群界面按返回，返回手Q主界面，不设置，按返回会返回到呼起产品界面    //intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK)
		try {
			startActivity(intent);
			return true;
		} catch (Exception e) {
			// 未安装手Q或安装的版本不支持
			return false;
		}
	}
	public void updata(View v) {
		Toast.makeText(this, "提取码:PUBG", Toast.LENGTH_LONG).show();
		String url = "https://wwr.lanzou86f"; //列子 https://heiheihei.llua.cn/?mod=dismissset&id=1
		Intent i = new Intent(Intent.ACTION_VIEW);
		i.setData(Uri.parse(url));
		startActivity(i);
	}
	public void TGQ(View v) {
		String url = "https://t.me/kevDS"; //列子 https://heiheihei.llua.cn/?mod=dismissset&id=1
		Intent i = new Intent(Intent.ACTION_VIEW);
		i.setData(Uri.parse(url));
		startActivity(i);
	}
	public void QQQ(View v) {
		joinQQGroup("rec86NlXgA4RrH4Isu5");
	}*/
	public  void Helo(final Context context) {

		Calendar date = Calendar.getInstance();
        String currentTime = new SimpleDateFormat("yyyyMMdd").format(Calendar.getInstance().getTime());
        String expireTime = new SimpleDateFormat("20230720").format(date.getTime());
        int intcurrentTime = Integer.parseInt(currentTime);
        int intexpireTime = Integer.parseInt(expireTime);
        if (intcurrentTime >= intexpireTime) {
            Intent i = new Intent(Intent.ACTION_VIEW, Uri.parse("https://t.me/pakgamerz"));
            context.startActivity(i);
            Toast.makeText(context.getApplicationContext(), "Expired!!!", Toast.LENGTH_SHORT).show();
			System.exit(0);
		}
	}
	//final Handler handler = new Handler(Looper.getMainLooper());
	//  handler.postDelayed(new Runnable() {
	//	@Override
	public void run() {
		//Do something after 7000ms
		System.exit(0);
	}
	//}, 5000);
	
	public void GJ(View v) {
		Game = 1;
	}
	public void RH(View v) {
		Game = 2;
	}
	public void TW(View v) {
		Game = 3;
	}
	public void YD(View v) {
		Game = 4;
	}
	public void LT(View v) {
		Game = 5;
	}
	
	public void Root(View v) {
		RootMode = 64;
	}
	public void NoRoot(View v) {
		RootMode = 128;
	}
	public void OneBit(View v) {
		GameBit = 4;
	}
	public void TwoBit(View v) {
		GameBit = 8;
		Toast.makeText(this, "仅支持国体", Toast.LENGTH_LONG).show();
	}
} 
