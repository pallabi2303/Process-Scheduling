#include<stdio.h>
#include<stdlib.h>
void swap(int arr[],int i,int j)
{
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}
int* bubble_sort(int arr[],int size)
{
    int* arr2=(int *)malloc(size*sizeof(int));
    //*arr2 copies the content of arr[]
    for(int i=0;i<size;i++)
    {
        arr2[i]=arr[i];
    }
    //arr2 is now sorted
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size-i-1;j++)
        {
            if(arr2[j]>arr2[j+1])
            {
                swap(arr2,j,j+1);
            }
        }
    }
    return arr2;
}

int main()
{
    int process;
    int time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d",&process);
    int arrival_time[process];
    int burst_time[process];
    int gantt_chart[process*10];
    int completion_time_in_ganttChart[process*10];
    int completion_time[process];
    int turn_around_time[process];
    int waiting_time[process];
    int response_time[process];
    int gantt_size=0;
    float avg_wt=0,avg_tat=0,avg_rt=0;
    for(int i=0;i<process;i++)
    {
        printf("Enter the arrival time of process%d : ",i+1);
        scanf("%d",&arrival_time[i]);
    }
    for(int i=0;i<process;i++)
    {
        printf("Enter the burst time of process%d : ",i+1);
        scanf("%d",&burst_time[i]);
    }
    int ask;
    printf("Do you want FCFS(0) or RR(1) scheduling? : ");
    scanf("%d",&ask);
    switch(ask)
    {
        case 0: fcfs(arrival_time,burst_time,process,gantt_chart,completion_time_in_ganttChart);
                break;
        case 1: 
                printf("Enter the time quantum: ");
                scanf("%d",&time_quantum);
                rr(arrival_time,burst_time,process,time_quantum,gantt_chart,completion_time_in_ganttChart);
                break;
    }
    printf("Gantt Chart : ");
    for(int i=0;;i++)
    {
        if(gantt_chart[i]>process)
           break;
        printf("%d, ",gantt_chart[i]+1);
        gantt_size++;
    } 
    printf("\n");
    //calculating completion time
    printf("\n");
    if(ask==0)
    {
        for(int i=0;i<process;i++)
        {
            completion_time[i]=completion_time_in_ganttChart[i];
        }
    }
    else
    {
        int y=0;
        for(int i=0;i<process;i++)
       {
           y+=burst_time[i];
       }
        for(int i=0;;i++)
        {
            if(gantt_chart[i]>process)
           break;
            completion_time[gantt_chart[i]]=completion_time_in_ganttChart[i];
            if(completion_time_in_ganttChart[i]==y)
               break;
        }
    }
    printf("Completion Time : ");
    for(int i=0;i<process;i++)
    {
        printf("%d, ",completion_time[i]);
    }
    for(int i=0;i<process;i++)
    {
        turn_around_time[i]=completion_time[i]-arrival_time[i];
    }
    printf("\nTurn Around Time : ");
    for(int i=0;i<process;i++)
    {
        printf("%d, ",turn_around_time[i]);
        avg_tat += turn_around_time[i];
    }
    avg_tat /= process*1.0; 
    for(int i=0;i<process;i++)
    {
        waiting_time[i]=turn_around_time[i]-burst_time[i];
    }
    printf("\nWaiting Time : ");
    for(int i=0;i<process;i++)
    {
        printf("%d, ",waiting_time[i]);
        avg_wt += waiting_time[i];
    }
    avg_wt /= process*1.0; 
    int check[process];
    for(int i=0;i<process;i++)
    {
        check[i]=0;
    }
    if(ask==0)
    {
        for(int i=0;i<process;i++)
        {
            response_time[i]=waiting_time[i];
            
        }
    }
    else
    {
        for(int i=0;i<process;i++)
        {
            for(int j=0;j<process*10;j++)
            {
                if(gantt_chart[j]==i )
                {
                    if (j==0)
                    {
                        response_time[i]=arrival_time[gantt_chart[0]];
                    }
                    else
                    {
                        response_time[i]=completion_time_in_ganttChart[j-1]-arrival_time[i];
                    }
                    break;
                }
            }
        }
    }
    printf("\nResponse Time : ");
    for(int i=0;i<process;i++)
    {
        printf("%d, ",response_time[i]);
        avg_rt += response_time[i];
    }
    avg_rt /= process*1.0;
    printf("\nAverage Turn Around Time = %f.\n",avg_tat);
    printf("Average Waiting Time = %f.\n",avg_wt);
    printf("Average Response Time = %f.\n",avg_rt);
    return 0;
}
