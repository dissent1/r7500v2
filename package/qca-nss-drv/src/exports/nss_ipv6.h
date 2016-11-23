/*
 **************************************************************************
 * Copyright (c) 2014 - 2015, The Linux Foundation. All rights reserved.
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all copies.
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 **************************************************************************
 */

/*
 * nss_ipv6.h
 *	NSS to HLOS interface definitions.
 */

/*
 * TODO: Since this is the now the public header file for writting an
 * IPv6 message, we need to convert the entire file to doxygen.
 */

#ifndef __NSS_IPV6_H
#define __NSS_IPV6_H

/**
 * IPv6 bridge/route rule messages
 */
enum nss_ipv6_message_types {
	NSS_IPV6_TX_CREATE_RULE_MSG,		/**< IPv6 create rule message */
	NSS_IPV6_TX_DESTROY_RULE_MSG,		/**< IPv6 destroy rule message */
	NSS_IPV6_RX_ESTABLISH_RULE_MSG,		/**< IPv6 establish rule message */
	NSS_IPV6_RX_CONN_STATS_SYNC_MSG,	/**< IPv6 connection stats sync message */
	NSS_IPV6_RX_NODE_STATS_SYNC_MSG,	/**< IPv6 generic statistics sync message */
	NSS_IPV6_TX_CONN_CFG_RULE_MSG,		/**< IPv6 connection cfg rule message */
	NSS_IPV6_MAX_MSG_TYPES,
};

/**
 * NSS IPv6 rule creation flags.
 */
#define NSS_IPV6_RULE_CREATE_FLAG_NO_SEQ_CHECK 0x01
					/**< Do not perform TCP sequence number checks */
#define NSS_IPV6_RULE_CREATE_FLAG_BRIDGE_FLOW 0x02
					/**< This is a pure bridge forwarding flow */
#define NSS_IPV6_RULE_CREATE_FLAG_ROUTED 0x04
					/**< Rule is for a routed connection */
#define NSS_IPV6_RULE_CREATE_FLAG_DSCP_MARKING 0x08
					/**< Rule has for a DSCP marking configured */
#define NSS_IPV6_RULE_CREATE_FLAG_VLAN_MARKING 0x10
					/**< Rule has for a VLAN marking configured */
#define NSS_IPV6_RULE_CREATE_FLAG_ICMP_NO_CME_FLUSH 0x20
					/**< Rule for not flushing CME on ICMP pkt */
#define NSS_IPV6_RULE_UPDATE_FLAG_CHANGE_MTU 0x40
					/**< Rule updation for MTU change */

/**
 * IPv6 rule creation validity flags.
 */
#define NSS_IPV6_RULE_CREATE_CONN_VALID 0x01		/**< IPv6 connection is valid */
#define NSS_IPV6_RULE_CREATE_TCP_VALID 0x02		/**< TCP protocol fields are valid */
#define NSS_IPV6_RULE_CREATE_PPPOE_VALID 0x04		/**< PPPoE fields are valid */
#define NSS_IPV6_RULE_CREATE_QOS_VALID 0x08		/**< QoS fields are valid */
#define NSS_IPV6_RULE_CREATE_VLAN_VALID 0x10		/**< VLAN fields are valid */
#define NSS_IPV6_RULE_CREATE_DSCP_MARKING_VALID 0x20	/**< DSCP marking fields are valid */
#define NSS_IPV6_RULE_CREATE_VLAN_MARKING_VALID 0x40	/**< VLAN marking fields are valid */

/**
 * Exception events from IPv6 bridge/route handler
 */
enum exception_events_ipv6 {
	NSS_EXCEPTION_EVENT_IPV6_ICMP_HEADER_INCOMPLETE,		/**<  NSS Exception event: ICMP protocol header incomplete */
	NSS_EXCEPTION_EVENT_IPV6_ICMP_UNHANDLED_TYPE,			/**<  NSS Exception event: ICMP protocol unhandled type */
	NSS_EXCEPTION_EVENT_IPV6_ICMP_IPV6_HEADER_INCOMPLETE,		/**<  NSS Exception event: ICMP IPv6 header incomplete */
	NSS_EXCEPTION_EVENT_IPV6_ICMP_IPV6_UDP_HEADER_INCOMPLETE,	/**<  NSS Exception event: ICMP IPv6 UDP header incomplete */
	NSS_EXCEPTION_EVENT_IPV6_ICMP_IPV6_TCP_HEADER_INCOMPLETE,	/**<  NSS Exception event: ICMP IPv6 TCP header incomplete */
	NSS_EXCEPTION_EVENT_IPV6_ICMP_IPV6_UNKNOWN_PROTOCOL,		/**<  NSS Exception event: ICMP IPv6 unknown protocol */
	NSS_EXCEPTION_EVENT_IPV6_ICMP_NO_ICME,				/**<  NSS Exception event: ICMP no IPv6 connection match entry */
	NSS_EXCEPTION_EVENT_IPV6_ICMP_FLUSH_TO_HOST,			/**<  NSS Exception event: ICMP flush the torn down connection to host*/
	NSS_EXCEPTION_EVENT_IPV6_TCP_HEADER_INCOMPLETE,			/**<  NSS Exception event: TCP protocol header incomplete */
	NSS_EXCEPTION_EVENT_IPV6_TCP_NO_ICME,				/**<  NSS Exception event: TCP protocol no IPv6 connection match entry */
	NSS_EXCEPTION_EVENT_IPV6_TCP_SMALL_HOP_LIMIT,			/**<  NSS Exception event: TCP protocol small hop limit reached */
	NSS_EXCEPTION_EVENT_IPV6_TCP_NEEDS_FRAGMENTATION,		/**<  NSS Exception event: TCP protocol needs fragmentation */
	NSS_EXCEPTION_EVENT_IPV6_TCP_FLAGS,				/**<  NSS Exception event: Unaccepted fast path TCP flags */
	NSS_EXCEPTION_EVENT_IPV6_TCP_SEQ_EXCEEDS_RIGHT_EDGE,		/**<  NSS Exception event: TCP sequence exceeds the right edge of the window */
	NSS_EXCEPTION_EVENT_IPV6_TCP_SMALL_DATA_OFFS,			/**<  NSS Exception event: TCP data offset is too short */
	NSS_EXCEPTION_EVENT_IPV6_TCP_BAD_SACK,				/**<  NSS Exception event: TCP SACK size is wrong */
	NSS_EXCEPTION_EVENT_IPV6_TCP_BIG_DATA_OFFS,			/**<  NSS Exception event: TCP data offset is too big */
	NSS_EXCEPTION_EVENT_IPV6_TCP_SEQ_BEFORE_LEFT_EDGE,		/**<  NSS Exception event: TCP sequence is before the left edge of the window */
	NSS_EXCEPTION_EVENT_IPV6_TCP_ACK_EXCEEDS_RIGHT_EDGE,		/**<  NSS Exception event: TCP ACK exceeds right edge of the window */
	NSS_EXCEPTION_EVENT_IPV6_TCP_ACK_BEFORE_LEFT_EDGE,		/**<  NSS Exception event: TCP ACK is before the left edge of the window */
	NSS_EXCEPTION_EVENT_IPV6_UDP_HEADER_INCOMPLETE,			/**<  NSS Exception event: UDP protocol header incomplete */
	NSS_EXCEPTION_EVENT_IPV6_UDP_NO_ICME,				/**<  NSS Exception event: UDP protocol no IPv6 connection match entry */
	NSS_EXCEPTION_EVENT_IPV6_UDP_SMALL_HOP_LIMIT,			/**<  NSS Exception event: UDP protocol small hop limit reached */
	NSS_EXCEPTION_EVENT_IPV6_UDP_NEEDS_FRAGMENTATION,		/**<  NSS Exception event: UDP protocol needs fragmentation */
	NSS_EXCEPTION_EVENT_IPV6_WRONG_TARGET_MAC,			/**<  NSS Exception event: IPv6 wrong target MAC address */
	NSS_EXCEPTION_EVENT_IPV6_HEADER_INCOMPLETE,			/**<  NSS Exception event: Incomplete IPv6 header */
	NSS_EXCEPTION_EVENT_IPV6_UNKNOWN_PROTOCOL,			/**<  NSS Exception event: IPv6 unknown protocol */
	NSS_EXCEPTION_EVENT_IPV6_IVID_MISMATCH,				/**<  NSS Exception event: IPv6 ingress vlan id mismatch */
	NSS_EXCEPTION_EVENT_IPV6_IVID_MISSING,				/**<  NSS Exception event: IPv6 ingress vlan id missing */
	NSS_EXCEPTION_EVENT_IPV6_DSCP_MARKING_MISMATCH,			/**<  NSS Exception event: IPv6 DSCP marking mismatch */
	NSS_EXCEPTION_EVENT_IPV6_VLAN_MARKING_MISMATCH,			/**<  NSS Exception event: IPv6 VLAN marking mismatch */
	NSS_EXCEPTION_EVENT_IPV6_INTERFACE_MISMATCH,			/**<  NSS Exception event: IPv6 source interface mismatch */
	NSS_EXCEPTION_EVENT_IPV6_GRE_NO_ICME,				/**<  NSS Exception event: GRE protocol no IPv6 conn match entry */
	NSS_EXCEPTION_EVENT_IPV6_GRE_NEEDS_FRAGMENTATION,		/**<  NSS Exception event: GRE protocol needs fragmentation */
	NSS_EXCEPTION_EVENT_IPV6_GRE_SMALL_HOP_LIMIT,			/**<  NSS Exception event: GRE protocol small hop limit reached */
	NSS_EXCEPTION_EVENT_IPV6_DESTROY,				/**<  NSS Exception event: Destroy */
	NSS_EXCEPTION_EVENT_IPV6_MAX					/**<  IPv6 exception events max type number */
};

/**
 * Common 5 tuple structure
 */
struct nss_ipv6_5tuple {
	uint32_t flow_ip[4];		/**< Flow IP address */
	uint32_t flow_ident;		/**< Flow ident (e.g. TCP/UDP port) */
	uint32_t return_ip[4];		/**< Return IP address */
	uint32_t return_ident;		/**< Return ident (e.g. TCP/UDP port) */
	uint8_t  protocol;		/**< Protocol number */
	uint8_t  reserved[3];		/**< Padded for alignment */
};

/**
 * Connection create structure
 */
struct nss_ipv6_connection_rule {
	uint16_t flow_mac[3];		/**< Flow MAC address */
	uint16_t return_mac[3];		/**< Return MAC address */
	int32_t flow_interface_num;	/**< Flow interface number */
	int32_t return_interface_num;	/**< Return interface number */
	uint32_t flow_mtu;		/**< Flow interface's MTU */
	uint32_t return_mtu;		/**< Return interface's MTU */
};

/**
 * PPPoE connection rules structure
 */
struct nss_ipv6_pppoe_rule {
	uint16_t flow_pppoe_session_id;	/**< Flow direction's PPPoE session ID. */
	uint16_t flow_pppoe_remote_mac[3];
					/**< Flow direction's PPPoE Server MAC address */
	uint16_t return_pppoe_session_id;
					/**< Return direction's PPPoE session ID. */
	uint16_t return_pppoe_remote_mac[3];
					/**< Return direction's PPPoE Server MAC address */
};

/**
 * DSCP connection rule structure
 */
struct nss_ipv6_dscp_rule {
	uint8_t flow_dscp;		/**< Egress DSCP value for flow direction */
	uint8_t return_dscp;		/**< Egress DSCP value for return direction */
	uint8_t reserved[2];		/**< Padded for alignment */
};

/**
 * VLAN connection rule structure
 */
struct nss_ipv6_vlan_rule {
	uint32_t ingress_vlan_tag;	/**< VLAN Tag for the ingress packets */
	uint32_t egress_vlan_tag;	/**< VLAN Tag for egress packets */
};

/**
 * TCP connection rule structure
 */
struct nss_ipv6_protocol_tcp_rule {
	uint32_t flow_max_window;	/**< Flow direction's largest seen window */
	uint32_t flow_end;		/**< Flow direction's largest seen sequence + segment length */
	uint32_t flow_max_end;		/**< Flow direction's largest seen ack + max(1, win) */
	uint32_t return_max_window;	/**< Return direction's largest seen window */
	uint32_t return_end;		/**< Return direction's largest seen sequence + segment length */
	uint32_t return_max_end;	/**< Return direction's largest seen ack + max(1, win) */
	uint8_t flow_window_scale;	/**< Flow direction's window scaling factor */
	uint8_t return_window_scale;	/**< Return direction's window scaling factor */
	uint16_t reserved;		/**< Padded for alignment */
};

/**
 * QoS connection rule structure
 */
struct nss_ipv6_qos_rule {
	uint32_t flow_qos_tag;		/**< QoS tag associated with this rule for flow direction */
	uint32_t return_qos_tag;	/**< QoS tag associated with this rule for return direction */
};

/**
 * Error types for ipv6 messages
 */
enum nss_ipv6_error_response_types {
	NSS_IPV6_CR_INVALID_PNODE_ERROR = 1,			/**< NSS Error: Invalid interface number */
	NSS_IPV6_CR_MISSING_CONNECTION_RULE_ERROR,		/**< NSS Error: Missing connection rule */
	NSS_IPV6_CR_BUFFER_ALLOC_FAIL_ERROR,			/**< NSS Error: Buffer allocation failure */
	NSS_IPV6_CR_PPPOE_SESSION_CREATION_ERROR,		/**< NSS Error: Unable to create PPPoE session */
	NSS_IPV6_DR_NO_CONNECTION_ENTRY_ERROR,			/**< NSS Error: No connection found to delete */
	NSS_IPV6_CR_CONN_CFG_ALREADY_CONFIGURED_ERROR,		/**< NSS Error: Conn cfg already done once */
	NSS_IPV6_CR_CONN_CFG_NOT_MULTIPLE_OF_QUANTA_ERROR,	/**< NSS Error: Conn cfg input is not multiple of quanta */
	NSS_IPV6_CR_CONN_CFG_EXCEEDS_LIMIT_ERROR,		/**< NSS Error: Conn cfg input exceeds max supported connections*/
	NSS_IPV6_CR_CONN_CFG_MEM_ALLOC_FAIL_ERROR,		/**< NSS Error: Conn cfg mem alloc fail at NSS FW */
	NSS_IPV6_UNKNOWN_MSG_TYPE,				/**< NSS Error: Unknown error */
};

/**
 * The IPv6 rule create sub-message structure.
 */
struct nss_ipv6_rule_create_msg {
	/*
	 * Request
	 */
	uint16_t valid_flags;				/**< Bit flags associated with the validity of parameters */
	uint16_t rule_flags;				/**< Bit flags associated with the rule */
	struct nss_ipv6_5tuple tuple;			/**< Holds values of the 5 tuple */
	struct nss_ipv6_connection_rule conn_rule;	/**< Basic connection specific data */
	struct nss_ipv6_protocol_tcp_rule tcp_rule;	/**< Protocol related accleration parameters */
	struct nss_ipv6_pppoe_rule pppoe_rule;		/**< PPPoE related accleration parameters */
	struct nss_ipv6_qos_rule qos_rule;		/**< QoS related accleration parameters */
	struct nss_ipv6_dscp_rule dscp_rule;		/**< DSCP related accleration parameters */
	struct nss_ipv6_vlan_rule vlan_primary_rule;	/**< VLAN related accleration parameters */
	struct nss_ipv6_vlan_rule vlan_secondary_rule;	/**< VLAN related accleration parameters */

	/*
	 * Response
	 */
	uint32_t index;					/**< Slot ID for cache stats to host OS */
};

/**
 * The IPv6 rule destroy sub-message structure.
 */
struct nss_ipv6_rule_destroy_msg {
	struct nss_ipv6_5tuple tuple;	/**< Holds values of the 5 tuple */
};

/**
 * The IPv6 rule conn cfgsub-message structure.
 */
struct nss_ipv6_rule_conn_cfg_msg {
	uint32_t num_conn;	/**< Holds number of supported connections in IPv6 */
};

/**
 * The NSS IPv6 rule establish structure.
 */
struct nss_ipv6_rule_establish {
	uint32_t index;				/**< Slot ID for cache stats to host OS */
	uint8_t protocol;			/**< Protocol number */
	uint8_t reserved[3];			/**< Reserved to align fields */
	int32_t flow_interface;			/**< Flow interface number */
	uint32_t flow_mtu;			/**< MTU for flow interface */
	uint32_t flow_ip[4];			/**< Flow IP address */
	uint32_t flow_ident;			/**< Flow ident (e.g. port) */
	uint16_t flow_mac[3];			/**< Flow direction source MAC address */
	uint16_t flow_pppoe_session_id;		/**< Flow direction`s PPPoE session ID. */
	uint16_t flow_pppoe_remote_mac[3];	/**< Flow direction`s PPPoE Server MAC address */
	uint16_t ingress_vlan_tag;		/**< Ingress VLAN tag */
	int32_t return_interface;		/**< Return interface number */
	uint32_t return_mtu;			/**< MTU for return interface */
	uint32_t return_ip[4];			/**< Return IP address */
	uint32_t return_ident;			/**< Return ident (e.g. port) */
	uint16_t return_mac[3];			/**< Return direction source MAC address */
	uint16_t return_pppoe_session_id;	/**< Return direction's PPPoE session ID. */
	uint16_t return_pppoe_remote_mac[3];	/**< Return direction's PPPoE Server MAC address */
	uint16_t egress_vlan_tag;		/**< Egress VLAN tag */
	uint8_t flags;				/**< Bit flags associated with the rule */
	uint32_t qos_tag;			/**< QoS Tag */
};

/**
 * IPv6 rule sync reasons.
 */
#define NSS_IPV6_RULE_SYNC_REASON_STATS 0
					/**< Sync is to synchronize stats */
#define NSS_IPV6_RULE_SYNC_REASON_FLUSH 1
					/**< Sync is to flush a cache entry */
#define NSS_IPV6_RULE_SYNC_REASON_EVICT 2
					/**< Sync is to evict a cache entry */
#define NSS_IPV6_RULE_SYNC_REASON_DESTROY 3
					/**< Sync is to destroy a cache entry (requested by host OS) */
#define NSS_IPV6_RULE_SYNC_REASON_PPPOE_DESTROY 4
					/**< Sync is to destroy a cache entry which belongs to a particular PPPoE session */

/**
 * The NSS IPv6 rule sync structure.
 */
struct nss_ipv6_conn_sync {
	uint32_t index;			/**< Slot ID for cache stats to host OS */
	uint8_t protocol;		/**< Protocol number */
	uint32_t flow_ip[4];		/**< Flow IP address */
	uint32_t flow_ident;		/**< Flow ident (e.g. port) */
	uint32_t flow_max_window;	/**< Flow direction's largest seen window */
	uint32_t flow_end;		/**< Flow direction's largest seen sequence + segment length */
	uint32_t flow_max_end;		/**< Flow direction's largest seen ack + max(1, win) */
	uint32_t flow_rx_packet_count;	/**< Flow interface's RX packet count */
	uint32_t flow_rx_byte_count;	/**< Flow interface's RX byte count */
	uint32_t flow_tx_packet_count;	/**< Flow interface's TX packet count */
	uint32_t flow_tx_byte_count;	/**< Flow interface's TX byte count */
	uint16_t flow_pppoe_session_id; /**< Flow interface`s PPPoE session ID. */
	uint16_t flow_pppoe_remote_mac[3];
					/**< Flow interface's PPPoE remote server MAC address if there is any */
	uint32_t return_ip[4];		/**< Return IP address */
	uint32_t return_ident;		/**< Return ident (e.g. port) */
	uint32_t return_max_window;	/**< Return direction's largest seen window */
	uint32_t return_end;		/**< Return direction's largest seen sequence + segment length */
	uint32_t return_max_end;	/**< Return direction's largest seen ack + max(1, win) */
	uint32_t return_rx_packet_count;
					/**< Return interface's RX packet count */
	uint32_t return_rx_byte_count;	/**< Return interface's RX byte count */
	uint32_t return_tx_packet_count;
					/**< Return interface's TX packet count */
	uint32_t return_tx_byte_count;	/**< Return interface's TX byte count */
	uint16_t return_pppoe_session_id;
					/**< Return interface`s PPPoE session ID. */
	uint16_t return_pppoe_remote_mac[3];
					/**< Return interface's PPPoE remote server MAC address if there is any */
	uint32_t inc_ticks;		/**< Number of ticks since the last sync */
	uint32_t reason;		/**< Reason for the sync */
	uint8_t flags;			/**< Bit flags associated with the rule */
	uint32_t qos_tag;		/**< QoS Tag */
	uint32_t cause;			/**< Flush cause associated with the rule */
};

/**
 * NSS IPv6 node stats sync structure
 */
struct nss_ipv6_node_sync {
	struct nss_cmn_node_stats node_stats;
				/**< Common node stats for IPv6 */
	uint32_t ipv6_connection_create_requests;
				/**< Number of IPv6 connection create requests */
	uint32_t ipv6_connection_create_collisions;
				/**< Number of IPv6 connection create requests that collided with existing entries */
	uint32_t ipv6_connection_create_invalid_interface;
				/**< Number of IPv6 connection create requests that had invalid interface */
	uint32_t ipv6_connection_destroy_requests;
				/**< Number of IPv6 connection destroy requests */
	uint32_t ipv6_connection_destroy_misses;
				/**< Number of IPv6 connection destroy requests that missed the cache */
	uint32_t ipv6_connection_hash_hits;
				/**< Number of IPv6 connection hash hits */
	uint32_t ipv6_connection_hash_reorders;
				/**< Number of IPv6 connection hash reorders */
	uint32_t ipv6_connection_flushes;
				/**< Number of IPv6 connection flushes */
	uint32_t ipv6_connection_evictions;
				/**< Number of IPv6 connection evictions */
	uint32_t ipv6_fragmentations;
				/**< Number of successful IPv6 fragmentations */
	uint32_t ipv6_frag_fails;
				/**< Number of IPv6 fragmentation fails */
	uint32_t exception_events[NSS_EXCEPTION_EVENT_IPV6_MAX];
				/**< Number of IPv6 exception events */
};

/**
 * Message structure to send/receive IPv6 bridge/route commands
 */
struct nss_ipv6_msg {
	struct nss_cmn_msg cm;					/**< Message Header */
	union {
		struct nss_ipv6_rule_create_msg rule_create;	/**< Message: rule create */
		struct nss_ipv6_rule_destroy_msg rule_destroy;	/**< Message: rule destroy */
		struct nss_ipv6_rule_establish rule_establish;	/**< Message: rule establish confirmation */
		struct nss_ipv6_conn_sync conn_stats;		/**< Message: stats sync */
		struct nss_ipv6_node_sync node_stats;		/**< Message: node stats sync */
		struct nss_ipv6_rule_conn_cfg_msg rule_conn_cfg;/**< Message: rule conn cfg */
	} msg;
};

extern int nss_ipv4_conn_cfg;

/**
 * @brief Return the maximum number of IPv6 connections that the NSS acceleration engine supports
 *
 * @return int The number of connections that can be accelerated by the NSS
 */
int nss_ipv6_max_conn_count(void);

/**
 * Callback to be called when IPv6 message is received
 */
typedef void (*nss_ipv6_msg_callback_t)(void *app_data, struct nss_ipv6_msg *msg);

/**
 * @brief Transmit an IPv6 message to the NSS
 *
 * @param nss_ctx NSS context
 * @param msg The IPv6 message
 *
 * @return nss_tx_status_t The status of the Tx operation
 */
extern nss_tx_status_t nss_ipv6_tx(struct nss_ctx_instance *nss_ctx, struct nss_ipv6_msg *msg);

/**
 * @brief Register a notifier callback for IPv6 messages from NSS
 *
 * @param cb The callback pointer
 * @param app_data The application context for this message
 *
 * @return struct nss_ctx_instance * The NSS context
 */
extern struct nss_ctx_instance *nss_ipv6_notify_register(nss_ipv6_msg_callback_t cb, void *app_data);

/**
 * @brief Un-register a notifier callback for IPv6 messages from NSS
 *
 * @return none
 */
extern void nss_ipv6_notify_unregister(void);

/**
 * @brief Get the NSS context which is managing IPv6
 *
 * @return struct nss_ctx_instance * The NSS context
 */
extern struct nss_ctx_instance *nss_ipv6_get_mgr(void);

/**
 * @brief Register IPv6 message handler
 *
 * @return none
 */
extern void nss_ipv6_register_handler(void);

/**
 * @brief IPv4 sysctl register
 *
 * @return None
 */
extern void nss_ipv6_register_sysctl(void);

/**
 * @brief IPv4 sysctl unregister
 *
 * @return None
 */
extern void nss_ipv6_unregister_sysctl(void);

/**
 * @brief NSS IPv6 message init
 *	Initialize NSS IPv6 specific message
 */
extern void nss_ipv6_msg_init(struct nss_ipv6_msg *nim, uint16_t if_num, uint32_t type, uint32_t len,
			nss_ipv6_msg_callback_t *cb, void *app_data);

#endif /* __NSS_IPV6_H */
