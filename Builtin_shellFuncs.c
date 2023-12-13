#include "shell.h"
/**
 * _mycd - Changes the current directory of the process
 * @info: Structure containing potential arguments
 *
 * Return: Always returns 0
 */
int _mycd(info_t *info)
{
	char *currentDir, *directory, buffer[1024];
	int chdirReturn;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		directory = _getenv(info, "HOME=");
		if (!directory)
			chdirReturn = /* TODO: what should this be? */
				chdir((directory = _getenv(info, "PWD=")) ? directory : "/");
		else
			chdirReturn = chdir(directory);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirReturn = /* TODO: what should this be? */
			chdir((directory = _getenv(info, "OLDPWD=")) ? directory : "/");
	}
	else
		chdirReturn = chdir(info->argv[1]);
	if (chdirReturn == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myexit - To exit the shell
 * @info: Structure containing potential arguments
 *
 * Return: Exits with a given exit status:
 *         (0) if info->argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitCheck;

	if (info->argv[1])  /* Checks for an exit argument */
	{
		exitCheck = _erratoi(info->argv[1]);
		if (exitCheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _myhelp - For displaying help information
 * @info: Structure containing potential arguments
 *
 * Return: Always returns 0
 */
int _myhelp(info_t *info)
{
	char **argsArray;

	argsArray = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argsArray); /* Temporary unused workaround */
	return (0);
}
