package com.abenk.in;

import android.app.Activity;
import android.app.Dialog;
import android.content.Intent;
import android.os.Bundle;
import android.graphics.Color;
import android.os.Build;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.RelativeLayout;
import com.saadahmedsoft.popupdialog.PopupDialog;
import com.saadahmedsoft.popupdialog.Styles;
import com.saadahmedsoft.popupdialog.listener.OnDialogButtonClickListener;


public class LoginActivity extends Activity {
    RelativeLayout GuestUser,premiumuser,adminuser;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        if (Build.VERSION.SDK_INT >= 21) {
            getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_LAYOUT_STABLE | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN);
        }

        setContentView(R.layout.activity_login);
        GuestUser = findViewById(R.id.guestuser);
        premiumuser = findViewById(R.id.premiumUser);
        adminuser = findViewById(R.id.adminUser);

        adminuser.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                PopupDialog.getInstance(LoginActivity.this)
                        .setStyle(Styles.FAILED)
                        .setHeading("Uh-Oh")
                        .setDescription("Your ip is not authorised"+
                                " Try again later.")
                        .setCancelable(false)
                        .showDialog(new OnDialogButtonClickListener() {
                            @Override
                            public void onDismissClicked(Dialog dialog) {
                                super.onDismissClicked(dialog);
                            }
                        });
            }
        });

        premiumuser.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                PopupDialog.getInstance(LoginActivity.this)
                        .setStyle(Styles.FAILED)
                        .setHeading("Uh-Oh")
                        .setDescription("Your ip is not authorised"+
                                " Try again later.")
                        .setCancelable(false)
                        .showDialog(new OnDialogButtonClickListener() {
                            @Override
                            public void onDismissClicked(Dialog dialog) {
                                super.onDismissClicked(dialog);
                            }
                        });
            }
        });

        GuestUser.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                startActivity(new Intent(LoginActivity.this,MainActivity.class));
            }
        });

        changeStatusBarColor();
    }

    private void changeStatusBarColor() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            Window window = getWindow();
            window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
            window.setStatusBarColor(Color.TRANSPARENT);
        }
    }
}