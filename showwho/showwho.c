#include <unistd.h>
#include <stdio.h>

static const char mnt_script[] = {
	"FSTYPE=\"%s\"\n"
	"FILE2MNT=\"%s\"\n"
	"LOOPDEV=`losetup -f`"
	"[ \"x$LOOPDEV\" = \"x\" ] && exit\n"
	"LOOPDEV=${LOOPDEV##/dev/}\n"
	"mkdir \"/mnt/$LOOPDEV\"\n" 
	"mount -t $FSTYPE -o loop,utf8,nosuid,nodev \"$FILE2MNT\" \"/mnt/$LOOPDEV\"\n"
};

int main(int argc, char *argv[])
{
	printf("call: %s\n", argv[1]);
	seteuid(0);
	perror("d");
	printf("uid: %d, euid: %d\n", getuid(), geteuid());

	execl("/bin/sh", "-c", script);
	
	return 0;
}
