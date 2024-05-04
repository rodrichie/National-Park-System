Smart National Park System
This repository contains the code and documentation for a Smart National Park System, designed to automate fee collection, tourist entry, and exit into a national park. The system includes features such as vehicle detection, fee collection, capacity management, and a user-friendly interface for park attendants.

Features
Entry Gate Automation:
Vehicle detection using a bridge and ATMEGA microcontroller.
Buzzer and LCD screen for signaling attendants.
Registration of car occupants, including children and adults.
Free entrance for drivers.
Capacity Management:
Monitoring park capacity to prevent entry when full.
Fee Collection:
Self-service fridge for water bottle purchases.
Keypad input for selecting bottle quantity.
Transaction cost calculation and fund acceptance.
Dispensing water bottles using a motorized system.
Exit Gate Automation:
Similar process to entry gate, including car registration.
Serial Console Interface:
Menu-based interface for attendants with various commands.
Check statistics, control the fridge, and collect funds.
Configuration and Storage:
Configuration settings stored in EEPROM for persistence.
Settings include entrance fees and park capacity.
Assumptions
The system starts with no tourists inside the park.
Security measures are in place for sensitive functions.
The system can handle the park's capacity and prevent entry when full.
The password for fridge replenishment is stored in EEPROM for security.
Drivers enter the park for free.
Funds collected are monitored and collected by the attendant.
The system calculates transaction costs for purchasing water bottles.
Motorized dispensing of water bottles operates efficiently.
How Data is Stored in EEPROM
Data in EEPROM is stored by writing electrical charges to specific memory locations. When writing data, bits are programmed by trapping or releasing electrons in a floating gate. Read operations detect the charge state of the cell, interpreting it as data. EEPROM is non-volatile, retaining data even when power is removed.

Usage
Clone the repository:
bash
Copy code
git clone git@github.com:rodrichie/National-Park-System.git
Upload the code to your microcontroller.
Follow the instructions in the documentation to configure the system.



