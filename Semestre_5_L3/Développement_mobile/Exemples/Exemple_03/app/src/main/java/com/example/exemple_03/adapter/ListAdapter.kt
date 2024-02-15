package com.example.exemple_03.adapter

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.ImageView
import android.widget.LinearLayout
import android.widget.TextView
import com.example.exemple_03.R
import com.example.exemple_03.data.ListData

class ListAdapter(context: Context, dataArrayList: ArrayList<ListData?>?) :
    ArrayAdapter<ListData?>(context, R.layout.theitem, dataArrayList!!) {

    override fun getView(position: Int, view: View?, parent: ViewGroup): View {
        var view = view
        val listData = getItem(position)

        if (view == null) {
            view = LayoutInflater.from(context).inflate(R.layout.theitem, parent, false)
        }

        val listImage = view!!.findViewById<ImageView>(R.id.item_image)
        val listName = view.findViewById<TextView>(R.id.item_text)

        listImage.setImageResource(listData!!.image)
        listName.text = listData.text

        return view
    }

}