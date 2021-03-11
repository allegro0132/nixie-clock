import driver
import time
while 1:
    driver.SendData(str(time.localtime( time.time() )[5])+str(time.localtime( time.time() )[5])+str(time.localtime( time.time() )[5]))
    driver.Latch()