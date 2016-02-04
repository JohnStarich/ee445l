# Lab 2: Performance Debugging

## Preparation

* They hold the addresses to read and write to.
* Approximately 125 ns.
* Load one is the addresse of PF1, load two is the value of PF1.
* We could load R1 with the address of PF1 first and then load the value into R0. Then do the EOR on R0 and store back into the address in R1. This would eliminate one of the loads which was redundant.
* No, the two read/writes do not create a critical section because they use the bit specific addresses for Port F. That makes them atomic operations via the bit banding memory addressing, meaning they can't change anything other than the pin that is being written to.


