//
//  Places.swift
//  Homework2
//
//  Created by jpjacks1 on 10/24/15.
//  Copyright (c) 2015 jpjacks1. All rights reserved.
//

import Foundation
import CoreData

class Places: NSManagedObject {

    @NSManaged var name: String
    @NSManaged var image: NSData
    @NSManaged var information: String
    @NSManaged var long: String
    @NSManaged var lati: String

}
