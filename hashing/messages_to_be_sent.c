#include <string.h>
#include <stdio.h>
#include <time.h>
#define MAX_END_NODES 100

typedef enum {
	BROADCAST=1,UNICAST=2,CONTROL=3
}MESSAGE_TYPE;	
typedef struct message_format{
	int sender_id;		//port number of the sender 
	int receiver_id;	//port number of the receiver (on which it listens)
	MESSAGE_TYPE msg_type;
	time_t timestamp ;	// =time(NULL);seconds since January 1, 1970;

}msg ;

msg *messages_to_be_sent_from_end_nodes[MAX_END_NODES];
int end_node_flag[MAX_END_NODES];

void initialize_queue(){
	memset(end_node_flag,0,MAX_END_NODES);
}

int enqueue_msg_to_send_from_end_node(msg *new_msg){
	if(end_node_flag[new_msg->sender_id]==1){
		printf("There's already a message pending to be sent.\nPress 1 to try again\n");
		return -1;
	}
	else if(end_node_flag[new_msg->sender_id]==0){
		//maybe a seg core dump here.
		messages_to_be_sent_from_end_nodes[new_msg->sender_id]=(msg *)malloc(sizeof(msg));
		messages_to_be_sent_from_end_nodes[new_msg->sender_id]=new_msg;
		end_node_flag[new_msg->sender_id]=1;
		printf("Message has been enqueued.Press 2 to continue.\n");
		return 1;
	}
	return -666;		//some other error while enqueuing.
}

// number of messages pending is returned.
int poll_for_message_check(int node_id){
	return end_node_flag[node_id];
}
msg *dequeue_message_to_send(int node_id){
	if(end_node_flag[node_id]==0){
		printf("There's no messsage to be dequeued.Check again\n");
		return NULL;
	}
	else{
		end_node_flag[node_id]=0;
		return messages_to_be_sent_from_end_nodes[node_id];
	}
	printf("Error occured while dequeuing\n");
	return NULL;
 }
