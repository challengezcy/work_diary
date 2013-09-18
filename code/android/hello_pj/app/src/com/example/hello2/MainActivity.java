package com.example.hello2;

import com.example.hello2.R;
import android.app.Activity;
import android.os.ServiceManager;
import android.os.Bundle;
import android.os.IHelloService;
import android.os.RemoteException;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends Activity implements OnClickListener {
	private final static String LOG_TAG = "shy.luo.renju.Hello";
	
	private IHelloService helloService = null;

	private EditText valueText = null;
	private Button readButton = null;
	private Button writeButton = null;
	private Button clearButton = null;	

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
    	helloService = IHelloService.Stub.asInterface(ServiceManager.getService("hello"));
    	        
    	valueText = (EditText)findViewById(R.id.edit_value);
    	readButton = (Button)findViewById(R.id.button_read);
    	writeButton = (Button)findViewById(R.id.button_write);
    	clearButton = (Button)findViewById(R.id.button_clear);

    	readButton.setOnClickListener(this);
    	writeButton.setOnClickListener(this);
    	clearButton.setOnClickListener(this);     
    	
    	Log.i(LOG_TAG, "Hello Activity Created");
    }
    
    @Override
    public void onClick(View v) {
    	if(v.equals(readButton)) {
		try {
    			int val = helloService.getVal();
    			String text = String.valueOf(val);
    			valueText.setText(text);
			Log.e(LOG_TAG, "===> Read value");
		} catch (RemoteException e) {
			Log.e(LOG_TAG, "Remote Exception while reading value from device.");
		}		
    	}
    	else if(v.equals(writeButton)) {
		try {
    			String text = valueText.getText().toString();
    			int val = Integer.parseInt(text);
			helloService.setVal(val);
			Log.e(LOG_TAG, "===> Write value");
		} catch (RemoteException e) {
			Log.e(LOG_TAG, "Remote Exception while writing value to device.");
		}
    	}
    	else if(v.equals(clearButton)) {
    		String text = "";
    		valueText.setText(text);
    	}
    }
/*
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
*/  
}
