public void onCreate(SQLiteDatabase db) {
    db.execSQL("CREATE TABLE " + NotePad.Notes.TABLE_NAME + " ("
            + NotePad.Notes._ID + " INTEGER PRIMARY KEY,"
            + NotePad.Notes.COLUMN_NAME_TITLE + " TEXT,"
            + NotePad.Notes.COLUMN_NAME_NOTE + " TEXT,"
            + NotePad.Notes.COLUMN_NAME_CREATE_DATE + " INTEGER,"
            + NotePad.Notes.COLUMN_NAME_MODIFICATION_DATE + " INTEGER"
            + NotePad.Notes.COLUMN_NAME_TEXT_COLOR + "INTEGER" //新增加的修改字体颜色
            + NotePad.Notes.COLUMN_NAME_TEXT_SIZE + "INTEGER" //新增加的修改字体大小
            + ");");
}
Long now = Long.valueOf(System.currentTimeMillis());
1
if (values.containsKey(NotePad.Notes.COLUMN_NAME_CREATE_DATE) == false) {
    values.put(NotePad.Notes.COLUMN_NAME_CREATE_DATE, now);
}
// If the values map doesn't contain the modification date, sets the value to the current time.
if (values.containsKey(NotePad.Notes.COLUMN_NAME_MODIFICATION_DATE) == false) {
    values.put(NotePad.Notes.COLUMN_NAME_MODIFICATION_DATE, now);
}
Date date = new Date(now);
SimpleDateFormat format = new SimpleDateFormat("yy.MM.dd HH:mm:ss");
String dateTime = format.format(date);
private static final String[] PROJECTION = new String[] {
        NotePad.Notes._ID, // 0
        NotePad.Notes.COLUMN_NAME_TITLE, // 1
        NotePad.Notes.COLUMN_NAME_MODIFICATION_DATE,//在这里加入了修改时间的显示
};
//NoteList使用SimpleCursorAdapter来装配数据，首先查询数据库的内容，
// 如下代码所示，这里使用ContentProvider默认的URI。
Cursor cursor = managedQuery(
    getIntent().getData(),            // Use the default content URI for the provider.
    PROJECTION,                       // Return the note ID and title for each note.
    null,                             // No where clause, return all records.
    null,                             // No where clause, therefore no where column values.
    NotePad.Notes.DEFAULT_SORT_ORDER  // Use the default sort order.
);
String[] dataColumns = {
        NotePad.Notes.COLUMN_NAME_TITLE,
        NotePad.Notes.COLUMN_NAME_MODIFICATION_DATE
} ;
int[] viewIDs = { android.R.id.text1 ,R.id.text2};
// Creates the backing adapter for the ListView.
//然后通过SimpleCursorAdapter来进行装配：
SimpleCursorAdapter adapter
    = new SimpleCursorAdapter(
              this,                             // The Context for the ListView
              R.layout.noteslist_item,          // Points to the XML for a list item
              cursor,                           // The cursor to get items from
              dataColumns,
              viewIDs
      );
case R.id.menu_search:
    startActivity(new Intent(Intent.ACTION_SEARCH,getIntent().getData()));
    return true;
    startActivity(new Intent(Intent.ACTION_SEARCH,getIntent().getData()));
    <activity
        android:name=".NoteSearch"
        android:label="NoteSearch"
        >

        <intent-filter>
            <action android:name="android.intent.action.NoteSearch" />
            <action android:name="android.intent.action.SEARCH" />
            <action android:name="android.intent.action.SEARCH_LONG_PRESS" />
            <category android:name="android.intent.category.DEFAULT" />
            <data android:mimeType="vnd.android.cursor.dir/vnd.google.note" />
            <!--1.vnd.android.cursor.dir代表返回结果为多列数据-->
            <!--2.vnd.android.cursor.item 代表返回结果为单列数据-->
        </intent-filter>
    </activity>
    private static final String[] PROJECTION = new String[]{
            NotePad.Notes._ID, // 0
            NotePad.Notes.COLUMN_NAME_TITLE, // 1
            NotePad.Notes.COLUMN_NAME_MODIFICATION_DATE,//在这里加入了修改时间的显示
    };
    Intent intent = getIntent();// Gets the intent that started this Activity.
    // If there is no data associated with the Intent, sets the data to the default URI, which
    // accesses a list of notes.
    if (intent.getData()==null){
        intent.setData(NotePad.Notes.CONTENT_URI);
    }
    getListView().setOnCreateContextMenuListener(this);
   mSearchView = (SearchView)findViewById(R.id.search_view);//注册监听器
   mSearchView.setIconifiedByDefault(false); //显示搜索的天幕，默认只有一个放大镜图标
   mSearchView.setSubmitButtonEnabled(true); //显示搜索按钮
   mSearchView.setBackgroundColor(getResources().getColor(R.color.blue_green)); //设置背景颜色
   mSearchView.setOnQueryTextListener(this);
   @Override
   public boolean onQueryTextSubmit(String s) {
       return false;
   }
   @Override
       public boolean onQueryTextChange(String s) { //Test改变的时候执行的内容
           //Text发生改变时执行的内容
           String selection = NotePad.Notes.COLUMN_NAME_TITLE + " Like ? ";//查询条件
           String[] selectionArgs = { "%"+s+"%" };//查询条件参数，配合selection参数使用,%通配多个字符

           //查询数据库中的内容,当我们使用 SQLiteDatabase.query()方法时，就会得到Cursor对象， Cursor所指向的就是每一条数据。
           //managedQuery(Uri, String[], String, String[], String)等同于Context.getContentResolver().query()
           Cursor cursor = managedQuery(
                   getIntent().getData(),            // Use the default content URI for the provider.用于ContentProvider查询的URI，从这个URI获取数据
                   PROJECTION,                       // Return the note ID and title for each note. and modifcation date.用于标识uri中有哪些columns需要包含在返回的Cursor对象中
                   selection,                        // 作为查询的过滤参数，也就是过滤出符合selection的数据，类似于SQL的Where语句之后的条件选择
                   selectionArgs,                    // 查询条件参数，配合selection参数使用
                   NotePad.Notes.DEFAULT_SORT_ORDER  // Use the default sort order.查询结果的排序方式，按照某个columns来排序，例：String sortOrder = NotePad.Notes.COLUMN_NAME_TITLE
           );

           //一个简单的适配器，将游标中的数据映射到布局文件中的TextView控件或者ImageView控件中
           String[] dataColumns = { NotePad.Notes.COLUMN_NAME_TITLE ,  NotePad.Notes.COLUMN_NAME_MODIFICATION_DATE };
           int[] viewIDs = { android.R.id.text1 , R.id.text2 };
           SimpleCursorAdapter adapter = new SimpleCursorAdapter(
                   this,                   //context:上下文
                   R.layout.noteslist_item,         //layout:布局文件，至少有int[]的所有视图
                   cursor,                          //cursor：游标
                   dataColumns,                     //from：绑定到视图的数据
                   viewIDs                          //to:用来展示from数组中数据的视图
                                                    //flags：用来确定适配器行为的标志，Android3.0之后淘汰
           );
           setListAdapter(adapter);
           return true;
       }
   }
   String selection = NotePad.Notes.COLUMN_NAME_TITLE + " Like ? ";//查询条件
   String[] selectionArgs = { "%"+s+"%" };//查询条件参数，配合selection参数使用,%通配多个字符

   //查询数据库中的内容,当我们使用 SQLiteDatabase.query()方法时，就会得到Cursor对象， Cursor所指向的就是每一条数据。
   //managedQuery(Uri, String[], String, String[], String)等同于Context.getContentResolver().query()
   Cursor cursor = managedQuery(
           getIntent().getData(),            // Use the default content URI for the provider.用于ContentProvider查询的URI，从这个URI获取数据
           PROJECTION,                       // Return the note ID and title for each note. and modifcation date.用于标识uri中有哪些columns需要包含在返回的Cursor对象中
           selection,                        // 作为查询的过滤参数，也就是过滤出符合selection的数据，类似于SQL的Where语句之后的条件选择
           selectionArgs,                    // 查询条件参数，配合selection参数使用
           NotePad.Notes.DEFAULT_SORT_ORDER  // Use the default sort order.查询结果的排序方式，按照某个columns来排序，例：String sortOrder = NotePad.Notes.COLUMN_NAME_TITLE
   );
 //一个简单的适配器，将游标中的数据映射到布局文件中的TextView控件或者ImageView控件中
 String[] dataColumns = { NotePad.Notes.COLUMN_NAME_TITLE ,  NotePad.Notes.COLUMN_NAME_MODIFICATION_DATE };
 int[] viewIDs = { android.R.id.text1 , R.id.text2 };
 SimpleCursorAdapter adapter = new SimpleCursorAdapter(
         this,                   //context:上下文
         R.layout.noteslist_item,         //layout:布局文件，至少有int[]的所有视图
         cursor,                          //cursor：游标
         dataColumns,                     //from：绑定到视图的数据
         viewIDs                          //to:用来展示from数组中数据的视图
                                          //flags：用来确定适配器行为的标志，Android3.0之后淘汰
 );
 setListAdapter(adapter);
 return true;
