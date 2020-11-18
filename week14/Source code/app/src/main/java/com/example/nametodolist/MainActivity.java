package com.example.nametodolist;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    // Array to store tasks.
    List<String> taskList;
    // Adapter to provide views.
    ArrayAdapter<String> mAdapter;

    // Tag to keep track of log messages.
    private static final String TAG = "MainActivity";

    /**
     * Initialize application binding and the controls to the data source.
     * Copied directly from the slides.
     *
     * @param savedInstanceState - state of an application.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        taskList = new ArrayList<>();
        ListView mTaskListView = (ListView) findViewById(R.id.list_todo);
        mAdapter = new ArrayAdapter<String>(this,
                R.layout.todo_item,
                R.id.task_title,
                taskList);
        mTaskListView.setAdapter(mAdapter);
    }

    /**
     * Render the menu in the main activity.
     * Copied directly from the slides.
     *
     * @param menu - menu of an application.
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main_menu, menu);
        return super.onCreateOptionsMenu(menu);
    }

    /**
     * React to the user interactions with the menu items.
     * Copied directly from the slides.
     *
     * @param item - menu item.
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == R.id.action_add_task) {
            addTask();
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    /**
     * Create a new task.
     * Copied directly from the slides.
     */
    private void addTask() {
        final EditText taskEditText = new EditText(this);
        AlertDialog dialog = new AlertDialog.Builder(this)
                .setTitle("Add a new task.")
                .setMessage("What do you want to do next?")
                .setView(taskEditText)
                .setPositiveButton("Add", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        String task = String.valueOf(taskEditText.getText());
                        Log.d(TAG, "Task to add: " + task);
                        addItem(task);
                    }
                })
                .setNegativeButton("Cancel", null)
                .create();
        dialog.show();
    }


    /**
     * Remove a task while the button 'Delete' for a correspondent entry in list was clicked.
     *
     * @param deleteButton - clicked delete button.
     */
    public void removeTask(View deleteButton) {
        TextView textView = ((View) deleteButton.getParent()).findViewById(R.id.task_title);
        String task = String.valueOf(textView.getText());
        Log.d(TAG, "Task to remove: " + task);
        removeItem(task);
    }

    /**
     * Change a task name while the button 'Edit' for a correspondent entry in list was clicked.
     *
     * @param editButton - clicked edit button.
     */
    public void editTask(View editButton) {
        TextView textView = ((View) editButton.getParent()).findViewById(R.id.task_title);
        String toEdit = String.valueOf(textView.getText());
        final EditText taskEditText = new EditText(this);
        taskEditText.setText(toEdit);
        AlertDialog dialog = new AlertDialog.Builder(this)
                .setTitle("Edit a task.")
                .setMessage("What name should be assigned?")
                .setView(taskEditText)
                .setPositiveButton("Save", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        String taskNewText = String.valueOf(taskEditText.getText());
                        Log.d(TAG, "Task to edit: " + toEdit);
                        editItem(toEdit, taskNewText);
                    }
                })
                .setNegativeButton("Cancel", null)
                .create();
        dialog.show();
    }

    /**
     * Add new task item in the task list.
     * Copied directly from the slides.
     *
     * @param itemText - task to add.
     */
    private void addItem(String itemText) {
        taskList.add(itemText);
        mAdapter.notifyDataSetChanged();
        Log.d(TAG, "Task '" + itemText + "' was successfully added.");
    }

    /**
     * Remove a task item from the task list.
     * Copied directly from the slides.
     *
     * @param itemText - task to add.
     */
    private void removeItem(String itemText) {
        taskList.remove(itemText);
        mAdapter.notifyDataSetChanged();
        Log.d(TAG, "Task '" + itemText + "' was successfully removed.");
    }

    /**
     * Change name of existing in task list task.
     *
     * @param toEdit - name of a task that should be edited.
     * @param toSet  - new name of a task.
     */
    private void editItem(String toEdit, String toSet) {
        taskList.set(taskList.indexOf(toEdit), toSet);
        mAdapter.notifyDataSetChanged();
        Log.d(TAG, "Task '" + toEdit + "' was successfully renamed to'" + toSet + "'.");
    }
}