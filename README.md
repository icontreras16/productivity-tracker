Isaac Contreras

Sleep Tracker

**** DEPENDENCIES ****
This project requires the following dependencies to build and run:
- g++
- GNU Make

**** BUILDING ****
Once you have the required dependencies, and are in the directory
containing this README file, please do the following:
> make

**** RUNNING ****
When completely compiled, the executable "start" will be in the
same directory. To execute program:
> ./start

The following commands are supported:
  
  h [ help ]		produce this help message
  
  re [ record ]	[OPTIONS]	record sleep affecting factors for current day
       	      		
  be [ begin ]		begin a new sleep interval (will cancel any current intervals
  
  e [ end ] 		end and save current sleep interval
  
  ca [ cancel ]		cancel current sleep interval
  
  in [ intervals ]	display history of sleep intervals
  
  fa [ factors ] 	display recorded sleep factors for current day
  
  q [ quit ]	 	exit Sleep Tracker


The following options are supported by "record" command:

  -w, Worked out
  
  -d, Drank alcohol
  
  -s, Exposed to display screen at late hour
  
  -a, Ate at late hour
  
  -c, Had caffeine