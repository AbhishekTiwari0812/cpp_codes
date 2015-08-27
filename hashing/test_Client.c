#include <stdio.h>
#include <stdlib.h>




typedef enum {
	BROADCAST=1,UNICAST=2,CONTROL=3

}MESSAGE_TYPE;	

typedef struct message_format{
	int sender_id;		//port number of the sender 
	int receiver_id;	//port number of the receiver (on which it listens)
	MESSAGE_TYPE msg_type;
	time_t timestamp ;	// =time(NULL);seconds since January 1, 1970;
	char message[300];
}msg ;

extern int enqueue_msg_to_send_from_end_node(msg * new_msg);
extern void initialize_queue();
int main(){
	msg *new_msg;
	char c='y';
	initialize_queue();
	while(c=='y'){
		new_msg=(msg *)malloc(sizeof(msg));
		printf("Input the sender_id\n");
		scanf("%d",&(new_msg->sender_id));
		printf("Input the receiver_id\n");
		scanf("%d",&(new_msg->receiver_id));
		printf("Input the message type.\n1 for BROADCAST,2 for UNICAST,3 for CONTROL\n");
		scanf("%d",&(new_msg->msg_type));
		printf("Input the message\n");
		scanf(" %[^\n]s",new_msg->message);
		//set time stamp
		//set payload
		enqueue_msg_to_send_from_end_node(new_msg);
		printf("Do you want to send another message?\nPress y for \"YES\".\nAny other key (except power button) for \"NO\"\n");
		//scanf("%c",&c);
		c=getchar();
		c=getchar();
		putchar(c);
	}
	return 0;
}