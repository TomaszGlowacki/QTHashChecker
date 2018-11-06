
QTHashChecker v1.0

Created By Tomasz G³owacki

Program generates x files in given location.
each file is numbered. 
each file contains: 
	number
	date
	time
	hash

Secondly, program tries to find password by brute force generating hash on each file. 
however, each file have the same password... no matter for now. 


next features:
 - every file has to have diffrient password.
 - implement opencl.
 - implement cuda. 
 - implement time messurment. 
 - implement multithreathing to better increase progressbar, QCoreApplication::processEvents() could take much of CPU. 
 - write unit tests. 
