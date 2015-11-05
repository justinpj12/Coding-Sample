//
//  PlaceInfo.swift
//  Homework2
//
//  Created by jpjacks1 on 10/26/15.
//  Copyright (c) 2015 jpjacks1. All rights reserved.
//

import Foundation

class PlacesInfo {
    
    var thelist: [record] = []
    
    init()
    {
        var newItem = record(n: "Arizona.jpg", lo:"-112.1129" , la:"36.1069")
        thelist.append(newItem)
        newItem = record(n: "china.jpg", lo:"103.4561" , la:"37.4857")
        thelist.append(newItem)
        newItem = record(n: "desert.jpg", lo: "-112.3814", la:"32.9163")
        thelist.append(newItem)
        newItem = record(n: "egypt.jpg", lo: "31.1342", la:"29.9792")
        thelist.append(newItem)
        newItem = record(n: "island.jpg", lo: "-155.6658", la:"19.5429")
        thelist.append(newItem)
        newItem = record(n: "niagara_falls.jpg", lo:"-79.0712" , la:"43.0792")
        thelist.append(newItem)
        newItem = record(n: "paris.jpg", lo:"2.2944" , la:"48.8583")
        thelist.append(newItem)
        newItem = record(n: "snow.jpg", lo: "-65.4501", la:"-24.7926")
        thelist.append(newItem)
    }
    //let pickerData = ["Arizona.jpg","china.jpg","desert.jpg","egypt.jpg","island.jpg","niagara_falls.jpg","paris.jpg","snow.jpg"]
}

class record {
    var name: String
    var lon: String
    var lat: String
    
    init(n: String, lo: String, la: String)
    {
        name = n
        lon = lo
        lat = la
    }
    
}

