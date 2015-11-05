//
//  mapViewController.swift
//  Homework2
//
//  Created by jpjacks1 on 10/26/15.
//  Copyright (c) 2015 jpjacks1. All rights reserved.
//

import Foundation
import UIKit
import MapKit

class mapViewController: UIViewController{
    
    @IBOutlet weak var mapView: MKMapView!
    @IBOutlet weak var longLabel: UILabel!
    @IBOutlet weak var latiLabel: UILabel!
    @IBOutlet weak var mapTypeSel: UISegmentedControl!
    
    var pLon: CLLocationDegrees = CLLocationDegrees()
    var pLat: CLLocationDegrees = CLLocationDegrees()
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.longLabel.text = String(stringInterpolationSegment: pLon)
        self.latiLabel.text = String(stringInterpolationSegment: pLat)
        
        let coords = CLLocationCoordinate2D(latitude: pLat, longitude: pLon)
        let span: MKCoordinateSpan = MKCoordinateSpanMake(0.3, 0.3)
        let region: MKCoordinateRegion = MKCoordinateRegionMake(coords, span)
        self.mapView.setRegion(region, animated: true)
        
        let annotation = MKPointAnnotation()
        annotation.coordinate = coords
        self.mapView.addAnnotation(annotation)
        
        // Do any additional setup after loading the view.
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func mapViewSelType(sender: UISegmentedControl) {
        switch mapTypeSel.selectedSegmentIndex
        {
        case 0:
            self.mapView.mapType = MKMapType.Standard
        case 1:
            self.mapView.mapType = MKMapType.Satellite
        default:
            break;
        }
    }

}