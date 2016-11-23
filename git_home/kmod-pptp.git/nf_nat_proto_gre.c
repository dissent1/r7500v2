/*
 * nf_nat_proto_gre.c
 *
 * NAT protocol helper module for GRE.
 *
 * GRE is a generic encapsulation protocol, which is generally not very
 * suited for NAT, as it has no protocol-specific part as port numbers.
 *
 * It has an optional key field, which may help us distinguishing two
 * connections between the same two hosts.
 *
 * GRE is defined in RFC 1701 and RFC 1702, as well as RFC 2784
 *
 * PPTP is built on top of a modified version of GRE, and has a mandatory
 * field called "CallID", which serves us for the same purpose as the key
 * field in plain GRE.
 *
 * Documentation about PPTP can be found in RFC 2637
 *
 * (C) 2000-2005 by Harald Welte <laforge@gnumonks.org>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 *
 */

#include <linux/version.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/ip.h>

#include <net/netfilter/nf_nat.h>
#include <net/netfilter/nf_nat_rule.h>
#include <net/netfilter/nf_nat_protocol.h>
#include <linux/netfilter/nf_conntrack_proto_gre.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harald Welte <laforge@gnumonks.org>");
MODULE_DESCRIPTION("Netfilter NAT protocol helper module for GRE");

static int dni_gre_version_check = 1;
module_param(dni_gre_version_check, int, 0);
MODULE_PARM_DESC(dni_gre_version_check,
	"Flag to execute GRE Version check or not(1:open, 0:close)");

/* generate unique tuple ... */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)
static void
#else
static bool
#endif
gre_unique_tuple(struct nf_conntrack_tuple *tuple,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)
		 const struct nf_nat_ipv4_range *range,
#else
		 const struct nf_nat_range *range,
#endif
		 enum nf_nat_manip_type maniptype,
		 const struct nf_conn *ct)
{
	static u_int16_t key;
	__be16 *keyptr;
	unsigned int min, i, range_size;

	/* If there is no master conntrack we are not PPTP,
	   do not change tuples */
	if (!ct->master)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)
		return;
#else
		return false;
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)
	if (maniptype == NF_NAT_MANIP_SRC)
#else
	if (maniptype == IP_NAT_MANIP_SRC)
#endif
		keyptr = &tuple->src.u.gre.key;
	else
		keyptr = &tuple->dst.u.gre.key;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)
	if (!(range->flags & NF_NAT_RANGE_PROTO_SPECIFIED)) {
#else
	if (!(range->flags & IP_NAT_RANGE_PROTO_SPECIFIED)) {
#endif
		pr_debug("%p: NATing GRE PPTP\n", ct);
		min = 1;
		range_size = 0xffff;
	} else {
		min = ntohs(range->min.gre.key);
		range_size = ntohs(range->max.gre.key) - min + 1;
	}

	pr_debug("min = %u, range_size = %u\n", min, range_size);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)
	for (i = 0; ; ++key) {
		*keyptr = htons(min + key % range_size);
		if (++i == range_size || !nf_nat_used_tuple(tuple, ct))
			return;
	}
#else
	for (i = 0; i < range_size; i++, key++) {
		*keyptr = htons(min + key % range_size);
		if (!nf_nat_used_tuple(tuple, ct))
			return true;
	}
#endif

	pr_debug("%p: no NAT mapping\n", ct);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)
	return;
#else
	return false;
#endif
}

/* manipulate a GRE packet according to maniptype */
static bool
gre_manip_pkt(struct sk_buff *skb, unsigned int iphdroff,
	      const struct nf_conntrack_tuple *tuple,
	      enum nf_nat_manip_type maniptype)
{
	const struct gre_hdr *greh;
	struct gre_hdr_pptp *pgreh;
	const struct iphdr *iph = (struct iphdr *)(skb->data + iphdroff);
	unsigned int hdroff = iphdroff + iph->ihl * 4;

	/* pgreh includes two optional 32bit fields which are not required
	 * to be there.  That's where the magic '8' comes from */
	if (!skb_make_writable(skb, hdroff + sizeof(*pgreh) - 8))
		return false;

	greh = (void *)skb->data + hdroff;
	pgreh = (struct gre_hdr_pptp *)greh;

	/* we only have destination manip of a packet, since 'source key'
	 * is not present in the packet itself */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)
	if (maniptype != NF_NAT_MANIP_DST)
#else
	if (maniptype != IP_NAT_MANIP_DST)
#endif
		return true;
	switch (greh->version) {
	case GRE_VERSION_1701:
		/* We do not currently NAT any GREv0 packets.
		 * Try to behave like "nf_nat_proto_unknown" */
		break;
	case GRE_VERSION_PPTP:
		pr_debug("call_id -> 0x%04x\n", ntohs(tuple->dst.u.gre.key));
		pgreh->call_id = tuple->dst.u.gre.key;
		break;
	default:
		if (dni_gre_version_check != 0) {
			pr_debug("can't nat unknown GRE version\n");
			return false;
		} else {
			pr_debug("allow nat unknown GRE version\n");
			return true;
		}
	}
	return true;
}

static const struct nf_nat_protocol gre = {
	.protonum		= IPPROTO_GRE,
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,4,0)
	.me			= THIS_MODULE,
#endif
	.manip_pkt		= gre_manip_pkt,
	.in_range		= nf_nat_proto_in_range,
	.unique_tuple		= gre_unique_tuple,
#if defined(CONFIG_NF_CT_NETLINK) || defined(CONFIG_NF_CT_NETLINK_MODULE)
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,4,0)
	.range_to_nlattr	= nf_nat_proto_range_to_nlattr,
#endif
	.nlattr_to_range	= nf_nat_proto_nlattr_to_range,
#endif
};

static int __init nf_nat_proto_gre_init(void)
{
	return nf_nat_protocol_register(&gre);
}

static void __exit nf_nat_proto_gre_fini(void)
{
	nf_nat_protocol_unregister(&gre);
}

module_init(nf_nat_proto_gre_init);
module_exit(nf_nat_proto_gre_fini);

void nf_nat_need_gre(void)
{
	return;
}
EXPORT_SYMBOL_GPL(nf_nat_need_gre);