//
//  ViewController.swift
//  Homework2
//
//  Created by jpjacks1 on 10/24/15.
//  Copyright (c) 2015 jpjacks1. All rights reserved.
//

import UIKit
import CoreData

class ViewController: UIViewController, NSFetchedResultsControllerDelegate {

    @IBOutlet weak var placesTable: UITableView!
    
    var place:Places? = nil
    var context: NSManagedObjectContext = (UIApplication.sharedApplication().delegate as! AppDelegate).managedObjectContext!
    
    var dataViewController: NSFetchedResultsController = NSFetchedResultsController()
    
    func getFetchResultsController() -> NSFetchedResultsController {
        
        dataViewController = NSFetchedResultsController(fetchRequest: listFetchRequest(), managedObjectContext: context, sectionNameKeyPath: nil, cacheName: nil)
        
        return dataViewController
        
    }
    
    func listFetchRequest() -> NSFetchRequest {
        
        let fetchRequest = NSFetchRequest(entityName: "Places")
        let sortDescripter = NSSortDescriptor(key: "name", ascending: true)
        fetchRequest.sortDescriptors = [sortDescripter]
        return fetchRequest
        
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        dataViewController = getFetchResultsController()
        dataViewController.delegate = self
        dataViewController.performFetch(nil)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func controllerDidChangeContent(controller: NSFetchedResultsController) {
        self.placesTable.reloadData()
    }
    
    func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        let numberOfSections  = dataViewController.sections?.count
        return numberOfSections!
    }
    
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        let numberOfRowsInSection = dataViewController.sections?[section].numberOfObjects
        return numberOfRowsInSection!
    }
    
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = self.placesTable.dequeueReusableCellWithIdentifier("dataCell", forIndexPath: indexPath) as! UITableViewCell
        let placeInfo = dataViewController.objectAtIndexPath(indexPath) as! Places
        var name = placeInfo.name
        cell.textLabel?.text = "Name: \(name)"
        
        return cell
        
    }
    
    
    func tableView(tableView: UITableView!, canEditRowAtIndexPath indexPath: NSIndexPath!) -> Bool {
        return true
    }
    
    func tableView(tableView: UITableView!, commitEditingStyle editingStyle:   UITableViewCellEditingStyle, forRowAtIndexPath indexPath: NSIndexPath!) {
        if (editingStyle == UITableViewCellEditingStyle.Delete) {
            let record = dataViewController.objectAtIndexPath(indexPath) as! Places
            context.deleteObject(record)
            context.save(nil)
            
        }
    }
    
    override func  prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        
        if segue.identifier == "edit"
        {
            let cell = sender as! UITableViewCell
            let indexPath = self.placesTable.indexPathForCell(cell)
            let dest: DetailViewController =  segue.destinationViewController as! DetailViewController
            let row = dataViewController.objectAtIndexPath(indexPath!) as! Places
            dest.nItem = row
            
        }
        
    }


}

