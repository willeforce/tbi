@ECHO OFF
IF '%1'=='' GOTO ERROR
Echo Now installing,Please Wait...
JRTZ -u -y %1\>nul
ECHO
ECHO Install Complete.
ECHO Type "JRTZ" to run.
%1
cd\jrtz
GOTO END

:ERROR
ECHO    Usage:          install driver
ECHO    Example:        install c:

:END
