
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>

int main()
{
	struct	termios ttyinfo;	
						
	if ( tcgetattr( 0 , &ttyinfo ) == -1 ){  
		perror( "cannot get params about stdin");
		exit(1);
	}

	showbaud ( cfgetospeed( &ttyinfo ) );	
	
	printf("VINTER = ^%c\t", ttyinfo.c_cc[VINTR] - 1 + 'A');
	printf("VQUIT = ^%c\t", ttyinfo.c_cc[VQUIT]- 1 + 'A');
	printf("VERASE = ^%c\t", '?');
	printf("VKILL = ^%c\t\n", ttyinfo.c_cc[VKILL]- 1 + 'A');
	printf("VEOF = ^%c\t", ttyinfo.c_cc[VEOF]- 1 + 'A');
	printf("VMIN = ^%c\t", ttyinfo.c_cc[VMIN]- 1 + 'A');
	printf("VEOL = ^%c\t", ttyinfo.c_cc[VEOL]- 1 + 'A');
	printf("VTIME = ^%c\t\n", ttyinfo.c_cc[VTIME]- 1 + 'A');


	show_some_flags( &ttyinfo );	
	
	return 0;
}

int showbaud( int thespeed ){
	printf("spend  ");
	switch ( thespeed ){
		case B300:		printf("300\n");	break;
		case B600:		printf("600\n"); 	break;
		case B1200:		printf("1200\n"); 	break;
		case B1800:		printf("1800\n"); 	break;
		case B2400:		printf("2400\n"); 	break;
		case B4800:		printf("4800\n"); 	break;
		case B9600:		printf("9600\n"); 	break;
		case B19200:		printf("19200\n"); 	break;
		case B38400:	printf("38400\n"); 	break;
		default:	printf("Fast\n");	break;
	}
}

struct flaginfo { int	fl_value; char	*fl_name; };

struct flaginfo input_flags[] = {
		IGNBRK	,	"Ignore break condition",
		BRKINT	,	"Signal interrupt on break",
		IGNPAR	,	"Ignore chars with parity errors",
		PARMRK	,	"Mark parity errors",
		INPCK	,	"Enable input parity check",
		ISTRIP	,	"Strip character",
		INLCR	,	"Map NL to CR on input",
		IGNCR	,	"Ignore CR",
		ICRNL	,	"Map CR to NL on input",
		IXON	,	"Enable start/stop output control",
		IXOFF   ,	"Enable start/stop input control",
		0	,	NULL };

struct flaginfo output_flags[] = {
		OPOST	,	"Post-process output",
		ONLCR	,	"Map NL to CR-NL on output",
		OCRNL	,	"Map CR to NL on output",
		OFILL	,	"Use fill characters for delay",
		NLDLY	,	"Select newline delays",
		CRDLY	,	"Select carriage-return delays",
		TABDLY	,	"Select horizontal-tab delays",
		BSDLY	,	"Select backspace delays:",
		FFDLY	,	"Select form-feed delays",
		VTDLY	,	"Select vertical-tab delays",
		0	,	NULL };


struct flaginfo c_flags[] = {
		CSIZE	,	"Character size",
		CSTOPB	,	"Send two stop bits, else one",
		CREAD	,	"Enable receiver",
		PARENB	,	"Parity enable",
		PARODD	,	"Odd parity, else even",
		HUPCL	,	"Hang up on last close",
		CLOCAL	,	"Ignore modem status lines",
		0	,	NULL };

	   
struct flaginfo local_flags[] = {
		ISIG	,	"Enable signals",
		ICANON	,	"Canonical input (erase and kill)",
		ECHO	,	"Enable echo",
		ECHOE	,	"Echo ERASE as BS-SPACE-BS",
		ECHOK	,	"Echo KILL by starting new line",
		0	,	NULL };


int show_some_flags( struct termios *ttyp ){
	printf("c_iflag: \n");
	show_flagset( ttyp->c_iflag, input_flags );
	
	printf("c_oflag: \n");
	show_flagset( ttyp->c_oflag, output_flags );
	
	printf("c_cflag: \n");
	show_flagset( ttyp->c_cflag, c_flags );
	
	printf("c_lflag: \n");
	show_flagset( ttyp->c_lflag, local_flags );
}

int show_flagset( int thevalue, struct flaginfo thebitnames[] ){
	int	i;
	
	for ( i=0; thebitnames[i].fl_value ; i++ ) {
		printf( "  %s is ", thebitnames[i].fl_name);
		if ( thevalue & thebitnames[i].fl_value )
			printf("ON\n");
		else
			printf("OFF\n");
	}
}
