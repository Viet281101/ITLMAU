package com.example.exemple_03

import android.graphics.Color
import android.os.Bundle
import android.view.MotionEvent
import android.view.View
import android.view.View.OnTouchListener
import android.widget.ImageButton
import android.widget.ListView
import android.widget.ScrollView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.example.exemple_03.adapter.ListAdapter
import com.example.exemple_03.data.ListData


//import com.example.listviewkotpractice.databinding.ActivityMainBinding


class MainActivity : AppCompatActivity() {

    //Instanciation des variables de la classe
    /*private lateinit var items: Array<String>*/
    private var dataArrayList = ArrayList<ListData?>()
    private var listSize = 0
    private var newItem = 0
    private var listMaxSize = 10
    private var deleteFlag = 0
    private var lock = true

    override fun onCreate(savedInstanceState: Bundle?){ //Construction et initialisation
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //Initialisation variables

        //Initialisation functions
        generateList()
        touch()
    }

    private fun touch(){
        val add = findViewById<ImageButton>(R.id.add)
        val appStop = findViewById<ImageButton>(R.id.appStop)
        appStop.setOnClickListener {
            finish()
        }
        add.setOnClickListener {
            /*this.gestion.setImageResource(R.drawable.baseline_delete_24)*/
            addItem()
        }
    }

    private fun generateList(){
        /*val dataBody = ArrayAdapter<String>(this, R.layout.theitem, items)
        list.adapter = dataBody*/
        val list = findViewById<ListView>(R.id.list)

        val scrolling = findViewById<ScrollView>(R.id.scrolling)
        //Bout de code que j'ai trouvé sur le web: https://stackoverflow.com/questions/18367522/android-list-view-inside-a-scroll-view
        list.setOnTouchListener(OnTouchListener { v, event ->
            scrolling.requestDisallowInterceptTouchEvent(true)
            val action = event.actionMasked
            when (action) {
                MotionEvent.ACTION_UP -> scrolling.requestDisallowInterceptTouchEvent(false)
            }
            false
        })

        val listAdapter = ListAdapter(this, this.dataArrayList)
        var itemFlag = View(this)
        var itemColor = getColor(R.color.holo_purple)

        list.adapter = listAdapter
        list.isClickable = true
        list.setOnItemClickListener { parent, view, position, id ->
            /*this.gestion.setImageResource(R.drawable.baseline_delete_24)*/
            //Select only 1 item => flag
            this.lock = false
            itemFlag.setBackgroundColor(itemColor)
            view.setBackgroundColor(Color.RED)
            itemFlag = view
            if(position > this.listSize){
                Toast.makeText(this, "Veuillez selectionner un item a supprimer!", Toast.LENGTH_SHORT).show()
            } else {
                deleteItem(position)
            }
        }


    }

    private fun addItem(){
        if(this.listSize < this.listMaxSize) {
            val listData = ListData(R.drawable.baseline_android_24, "Item: "+this.newItem)
            this.dataArrayList.add(listData)
            this.listSize += 1
            this.newItem += 1
            generateList()
        }
        else{
            Toast.makeText(this, "Vous ne pouvez plus ajouter d'item!", Toast.LENGTH_SHORT).show()
        }
    }

    private fun deleteItem(item: Int){
        val delete = findViewById<ImageButton>(R.id.delete)
        delete.setImageResource(R.drawable.baseline_delete_24)
        delete.setOnClickListener {
            if(this.listSize == 0){
                Toast.makeText(this, "Il n'y a pas d'item à supprimer!", Toast.LENGTH_SHORT).show()
            } else if(!this.lock){
                this.dataArrayList.removeAt(item)
                delete.setImageResource(R.drawable.border)
                this.deleteFlag = item
                this.listSize -= 1
                this.lock = true
                generateList()
            } else {
                Toast.makeText(this, "Veuillez selectionner un item a supprimer!", Toast.LENGTH_SHORT).show()
            }
        }
    }

}