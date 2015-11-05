//
//  DetailViewController.swift
//  Homework2
//
//  Created by jpjacks1 on 10/24/15.
//  Copyright (c) 2015 jpjacks1. All rights reserved.
//

import Foundation
import UIKit
import CoreData
import MapKit


class DetailViewController: UIViewController, UIPickerViewDelegate, UIPickerViewDataSource, UINavigationControllerDelegate {
    
    @IBOutlet weak var name: UITextField!
    @IBOutlet weak var infoBox: UITextView!
    @IBOutlet weak var imageBox: UIImageView!
    @IBOutlet weak var picPicker: UIPickerView!
    @IBOutlet weak var imageName: UILabel!
    
    let insertContext = (UIApplication.sharedApplication().delegate as! AppDelegate).managedObjectContext
    
    var nItem:Places? = nil
    var pItem:PlacesInfo = PlacesInfo()
    var long: String = "";
    var lati: String = "";
    
    override func viewDidLoad() {
        super.viewDidLoad()
        picPicker.dataSource = self
        picPicker.delegate = self
        
        imageName.text = pickerView(picPicker, titleForRow: 0, forComponent: 0)
        if nItem != nil {
            name.text = nItem?.name
            imageBox.image = UIImage(data: nItem!.image as NSData)
            infoBox.text = nItem?.information
            long = nItem!.long
            lati = nItem!.lati
        }
        // Do any additional setup after loading the view.
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func saveData(sender: UIBarButtonItem) {
        
        if nItem == nil     // Save New Place
        {
            
            let ent = NSEntityDescription.entityForName("Places", inManagedObjectContext: self.insertContext!)
            
            let nItem = Places(entity: ent!, insertIntoManagedObjectContext: self.insertContext!)
            
            nItem.name = name.text
            nItem.information = infoBox.text
            nItem.image = UIImagePNGRepresentation(imageBox.image)
            nItem.long = long
            nItem.lati = lati
            
            self.insertContext?.save(nil)
        }
        else        // Save Edits to Existing
        {
            nItem!.name = name.text
            nItem!.information = infoBox.text
            nItem!.image = UIImagePNGRepresentation(imageBox.image)
            nItem!.long = long
            nItem!.lati = lati
            insertContext?.save(nil)
        }
        
        navigationController!.popViewControllerAnimated(true)

    }
    
    
    @IBAction func cancel(sender: UIBarButtonItem) {
        navigationController!.popViewControllerAnimated(true)
    }
    
    @IBAction func selectImage(sender: UIButton) {
        self.imageBox.image = UIImage(named: imageName.text!)

    }
    
    func numberOfComponentsInPickerView(pickerView: UIPickerView) -> Int{
        return 1
    }
    
    func pickerView(pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int{
        return pItem.thelist.count
    }
    
    func pickerView(pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String! {
        return pItem.thelist[row].name
    }
    
    func pickerView(pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int){
        imageName.text = pItem.thelist[row].name
        long = pItem.thelist[row].lon
        lati = pItem.thelist[row].lat
        self.view.endEditing(true)
    }

    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        
        if(segue.identifier == "mapView"){
            if let mapViewController: mapViewController = segue.destinationViewController as? mapViewController {

                mapViewController.pLon = (long as NSString).doubleValue;
                mapViewController.pLat = (lati as NSString).doubleValue;
            }
        }
    }
}