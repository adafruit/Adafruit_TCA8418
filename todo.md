
## TCA8418

### TODO


|  prio  |   topic                           | notes
|:------:|:----------------------------------|:--------|
|  low   |  reset pin                        | expend class with a reset pin
|        |                                   | can this be done in software?  (NOT FOUND)
|  low   | read interrupt register           | differentiate  (masks are defined)
|  low   | caching registers                 | performance
|  low   | "CAD" support                     | 8.3.4 Control-Alt-Delete Support
|  low   | gpio irq's read                   | 8.6.2.7 GPIO Interrupt Status Registers
|        |                                   |
|  low   | keypad locking                    | 8.6.2.6 Unlock1 and Unlock2 Registers
|  low   |                                   | 8.6.2.5 Keypad Lock1 to Lock2 Timer Register
|  low   |                                   | 8.6.2.3 Key Lock and Event Counter Register
|  low   |                                   | 8.3.2 Keypad Lock/Unlock
|  low   |                                   | 8.3.3 Keypad Lock Interrupt Mask Timer
|        |                                   |
|        |                                   |
|  med   | doxygen                           | check all code
|  low   | remove magic numbers from code    | check all code
|        |                                   |
|        |                                   | 
|        |                                   |
|        |                                   | 



### DONE

|  prio  |   topic                           | notes
|:------:|:----------------------------------|:--------|
|  high  | defines bit masks cfg reg (1)     | separate registers.h file
|  high  | defines bit masks stat reg (2)    | separate registers.h file
|  high  | gpio pull up                      | done
|  med   | set gpio event key                | 8.6.2.12 GPI Event Mode Registers
|  med   | debounce enable / disable         | 8.6.2.15 Debounce Disable Registers
|  med   | gpio irq's set as default         | 8.6.2.10 GPIO Interrupt Enable Registers
|  med   | irq falling rising per pin        | 8.6.2.14 GPIO Edge/Level Detect Registers
|        |                      |
|        |                      |
|        |                      |
|        |                      |
|        |                      |
|        |                      |
|        |                      |


### WONT

|  prio  |   topic                           | notes
|:------:|:----------------------------------|:--------|
|        | keyMapping nrs on e.g. chars?     | is this part of the lib?
|        |                                   |
|        |                                   | 

