##############################################
# $Id: myUtilsTemplate.pm 7570 2015-01-14 18:31:44Z rudolfkoenig $
#
# Save this file as 99_myUtils.pm, and create your own functions in the new
# file. They are then available in every Perl expression.

package main;

use strict;
use warnings;
use POSIX;
use Time::Local;

# apt-get install libnet-ping-external-perl
#use Net::Ping::External qw(ping); 
use Net::Ping;

sub mqttmsg{
	my @args = @_;
	my $topic=$args[0];
	my $msg="";
	my $cnt=scalar @args;
	foreach my $i (1..$#args){
		$msg.=" ".$args[$i];
	}
	$msg =~ s/^\s+|\s+$//g;
	qx(/usr/bin/mosquitto_pub -h 192.168.0.40 -t '$topic' -m '$msg' -q 1 -r);
}

...

1;
