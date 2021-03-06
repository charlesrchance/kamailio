#include <stdio.h>
#include "../../sr_module.h"
#include "../../dprint.h"
#include "../../error.h"
#include "../../modules/usrloc/usrloc.h"
#include "../usrloc/ul_callback.h"
#include "../../modules/sl/sl.h"
#include "../../mod_fix.h"

#include "usrloc_sync.h"

static int mod_init(void); 
static int child_init(int);

int enable_usrloc = 0;
int usrloc_syncflag = 2;

MODULE_VERSION

static param_export_t params[] = {
	{"enable", INT_PARAM, &enable_usrloc},
	{"flag", INT_PARAM, &usrloc_syncflag},
	{0, 0, 0}
};

struct module_exports exports = {
	"usrloc_dmq",				/* module name */
	DEFAULT_DLFLAGS,		/* dlopen flags */
	0,						/* exported functions */
	params,					/* exported parameters */
	0,						/* exported statistics */
	0,   					/* exported MI functions */
	0,						/* exported pseudo-variables */
	0,						/* extra processes */
	mod_init,				/* module initialization function */
	0,   					/* response handling function */
	0, 						/* destroy function */
	child_init              /* per-child init function */
};


static int mod_init(void)
{
		LM_ERR("dmq_sync loaded: usrloc=%d\n", enable_usrloc);
		
		if (enable_usrloc) {
			usrloc_dmq_flag = 1 << usrloc_syncflag;
			bind_usrloc_t bind_usrloc;
			
			bind_usrloc = (bind_usrloc_t)find_export("ul_bind_usrloc", 1, 0);
			if (!bind_usrloc) {
  				LM_ERR("can't bind usrloc\n");
				return -1;
			}
			if (bind_usrloc(&ul) < 0) {
				LM_ERR("Can't bind ul\n");
                return -1;
			}			
			if(ul.register_ulcb != NULL) {
				if(ul.register_ulcb(ULCB_MAX, ul_cb_contact, 0)< 0)
				{
					LM_ERR("can not register callback for expired contacts\n");
					return -1;
				}
			}					
			if (!usrloc_dmq_initialize()){
				LM_DBG("usrloc_dmq initialized\n");
			} else {
				LM_ERR("Error in usrloc_dmq_initialize()\n");
			}
		}
		return 0;
}

static int child_init(int rank)
{

	if (rank == PROC_MAIN) {
		LM_ERR("child_init PROC_MAIN\n");
		return 0;
	}
	if(rank == PROC_INIT || rank == PROC_TCP_MAIN) {
		LM_ERR("child_init PROC_INIT\n");
		return 0;
	}
	return 0;
}
