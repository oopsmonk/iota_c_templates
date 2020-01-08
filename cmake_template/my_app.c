#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"
#include "config.h"

void init_iota_client(iota_client_service_t *const service) {
  service->http.path = "/";
  service->http.content_type = "application/json";
  service->http.accept = "application/json";
  service->http.host = CONFIG_IRI_NODE_URI;
  service->http.port = CONFIG_IRI_NODE_PORT;
  service->http.api_version = 1;
#ifdef CONFIG_ENABLE_HTTPS
  service->http.ca_pem = ROOT_CA1_PEM;
#else
  service->http.ca_pem = NULL;
#endif
  service->serializer_type = SR_JSON;
  iota_client_core_init(service);
  iota_client_extended_init();
}

void get_iota_node_info(iota_client_service_t *iota_client_service) {
  retcode_t ret = RC_ERROR;
  // Allocate a response object
  get_node_info_res_t *node_response = get_node_info_res_new();

  // Connect to the node
  ret = iota_client_get_node_info(iota_client_service, node_response);

  // If the node returned data, print it to the console
  if (ret == RC_OK) {
    printf("appName %s \n", node_response->app_name->data);
    printf("appVersion %s \n", node_response->app_version->data);

    // shows the latest milestone hash to the console
    printf("latestMilestone ");
    flex_trit_print(node_response->latest_milestone, NUM_TRITS_HASH);
    printf("\n");

    printf("latestMilestoneIndex %u\n", (uint32_t)node_response->latest_milestone_index);
    printf("latestSolidSubtangleMilestoneIndex %u\n", (uint32_t)node_response->latest_solid_subtangle_milestone_index);

    printf("milestoneStartIndex %u\n", node_response->milestone_start_index);
    printf("neighbors %d \n", node_response->neighbors);
    printf("packetsQueueSize %d \n", node_response->packets_queue_size);
    printf("tips %u \n", node_response->tips);
    printf("transactionsToRequest %u\n", node_response->transactions_to_request);
    size_t num_features = get_node_info_req_features_num(node_response);
    for (; num_features > 0; num_features--) {
      printf("%s, ", get_node_info_res_features_at(node_response, num_features - 1));
      printf("\n");
    }

  } else {
    printf("Failed to connect to the node.");
  }

done:

  // Free the response object
  get_node_info_res_free(&node_response);
}

int main(void) {
  // Create and init the client service
  iota_client_service_t iota_client_service;
  init_iota_client(&iota_client_service);

  // Call the getNodeInfo endpoint
  get_iota_node_info(&iota_client_service);
}
