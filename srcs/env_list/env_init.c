#include "../../incls/prototypes.h"

static char		*extract_key(char *env_str, char **equals_sign);
static void		update_existing_node(t_env *node, const char *value_source,
								 char *key_to_transfer);
static t_env	*create_new_node(char *key_to_transfer, const char *value_source);
static void		add_env_node_transfer_key(t_env **env_list, char *key_to_transfer,
									   const char *value_source);
