# Logistics-App
This project is a **Transport Logistics Management System** built in C++. It allows users to manage vehicles (cars and trucks) and customer records through a menu-driven interface. Key features include adding, displaying, saving, and loading data for vehicles and customers, with file persistence for data retention. The system leverages object-oriented principles, supports error handling, and provides a simple yet functional command-line interface for fleet and customer management.

Key Features:
Vehicle Management:

Add Vehicles: Supports adding cars and trucks, with specific attributes like seating capacity for cars and payload capacity for trucks.
Display Vehicles: Lists all vehicles in the system.
Save Vehicles to File: Stores vehicle data into a text file for persistence.
Load Vehicles from File: Reads vehicle data from a text file, restoring it to the system.
Customer Management:

Add Customers: Collects and stores customer information (name and contact).
Display Customers: Displays all customer records.
Save Customers to File: Writes customer data into a file for later use.
Load Customers from File: Retrieves customer data from a file.
Data Persistence:

The program uses files (vehicles.txt and customers.txt by default) to save and load data, ensuring information is retained across sessions.
Object-Oriented Design:

Implements base and derived classes for vehicles (Vehicle, Car, Truck).
Uses polymorphism to manage different vehicle types seamlessly.
Includes exception handling for robust file parsing and error reporting.
Interactive Command-Line Menu:

Users can navigate through a menu to perform operations like adding vehicles or customers, saving/loading data, and viewing records.
