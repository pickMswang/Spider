#include <Spider.h>

int main(void)
{
		url_t * u_info;
		int webfd;
		ssl_t * ssl=NULL;
		queue_t  new;
		queue_t  old;
		//const char * tmpurl = "http://img.zcool.cn/community/018a1d57d761f60000012e7ece7fff.png@1280w_1l_2o_100sh.png";
		char * tmpurl = "https://wenku.baidu.com/view/6d880147284ac850ac024230.html";
		Spider_Queue_create(&new,100);
		Spider_Queue_create(&old,500);
		Spider_Queue_en(&new,tmpurl);
		Spider_Queue_show(&new);
		if((u_info = Spider_Analytic_url(Spider_Queue_de(&new)))!=NULL){
				printf("[1] Analytical URL Success:\nURL:%s\nDOMAIN:%s\nIP:%s\nPORT:%d\nNAME:%s\nTYPES:%d\n",u_info->url,u_info->domain,u_info->ip,u_info->port,u_info->name,u_info->types);
		}else
				printf("ERROR:Analytical URL Call Failed..\n");
		webfd = Spider_Connect_server(u_info);
		if(u_info->types){
				Spider_Request(u_info,webfd,ssl);
				Spider_Response(webfd,ssl);
		}else{
				ssl = Spider_Openssl_Create(webfd);
				Spider_Request(u_info,webfd,ssl);
				Spider_Response(webfd,ssl);
		}

		char * src = Spider_Create_cache("temp");
		Spider_Analytic_html(&new,src);
		Spider_Queue_show(&new);
		return 0;
}
