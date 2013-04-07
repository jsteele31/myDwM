#define NUMCOLORS 		13
#define MODKEY 			Mod4Mask
#define MONKEY 			Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

static const unsigned int systrayspacing	= 2;	    // systray spacing
static const Bool showsystray				= True;	    // false means no systray
static const unsigned int gappx				= 8;		// gaps between windows
static const unsigned int borderpx			= 1;        // border pixel of windows
static const unsigned int snap				= 32;       // snap pixel
static const Bool showbar					= True;     // false means no bar
static const Bool topbar					= True;     // false means bottom bar
static const float mfact					= 0.50; 	// factor of master area size [0.05..0.95]
static const int nmaster					= 1;   		// number of clients in master area
static const Bool resizehints				= False; 	// true means respect size hints in tiled resizals

static const char font[] = "-*-stlarch-medium-r-*-*-14-*-*-*-*-*-*-*";

static const char colors[NUMCOLORS][ColLast][13] = {
    /* border    fg       	bg */
	{ "#222222", "#f7f7d9", "#222222" },				// 01 - regular
	{ "#555555", "#dbf2c4", "#222222" },				// 02 - selected
	{ "#555555", "#f2dbc4", "#222222" },				// 03 - urgent
	{ "#222222", "#e9e99a", "#222222" }, 				// 04 - occupied
	{ "#222222", "#f2dbc4", "#222222" }, 				// 05 - red
	{ "#222222", "#f2c4c4", "#222222" }, 				// 06 - T-Red
	{ "#222222", "#f2f2c4", "#222222" }, 				// 07 - T-Yellow
	{ "#222222", "#c4f2f2", "#222222" }, 				// 08 - T-Teal
	{ "#222222", "#c4c4f2", "#222222" }, 				// 09 - T-Blue
	{ "#222222", "#f2dbc4", "#222222" }, 				// 0A - T-LRed
	{ "#222222", "#dbf2c4", "#222222" }, 				// 0B - T-LGreen
	{ "#FFFFFF", "#FFFFFF", "#222222" }, 				// 0C - white
	{ "#000000", "#000000", "#222222" }, 				// 0D - black
};

static const Layout layouts[] = {
	/*	symbol		gaps		arrange */
	{ "  T  ",		True,	    tile	},
	{ "  B  ",   	True,	    bstack	},
	{ "  M  ",  	False,	    monocle	},
	{ "  F  ",		False,	    NULL	},
};

static const Tag tags[] = {
	/* name			layout			mfact		nmaster */
	{ "  web  ",	&layouts[0],  	-1,		    -1 },
	{ "  chat  ",	&layouts[0],   	-1,		    -1 },
	{ "  term  ",	&layouts[3],  	-1,		    -1 },
	{ "  code  ",	&layouts[0],  	-1,			-1 },
	{ "  media  ",	&layouts[0],  	-1,			-1 },
	{ "  misc  ",	&layouts[0],  	-1,		    -1 },
};

static const Rule rules[] = {
    /* class         	instance   	title 	    tags mask    	isfloating		iscentred   	monitor */
	{ "trayer",		NULL,       NULL,       1 << 5,       	True,       	False,			-1 },
};

static const char *menu[] = { "dmenu_run", "-i", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *termcmd[]	   = { "xterm", NULL };
static const char *webcmd[]	   = { "chromium", NULL };
static const char *geditcmd[]	   = { "gedit", NULL };

static Key keys[] = {
	{ MODKEY|ShiftMask,	XK_q,     	quit,           {0} },
	{ MODKEY|ShiftMask,	XK_b,    	togglebar,      {0} },
	{ MODKEY|ShiftMask,	XK_c,   	killclient,     {0} },
	{ MONKEY,       	XK_Return,	zoom,           {0} },
	{ MODKEY,       	XK_d,		spawn,          {.v = menu } },
	{ MODKEY,       	XK_g,		spawn,          {.v = geditcmd } },
	{ MODKEY,       	XK_w,		spawn,          {.v = webcmd } },
	{ MODKEY,               XK_Return,      spawn,          {.v = termcmd } },
	{ MODKEY,          	XK_Tab,   	view,           {0} },
	{ MODKEY|ShiftMask,	XK_f,   	togglefloating, {0} },
	{ MODKEY,      		XK_space,	setlayout,      {0} },
	{ MODKEY,		XK_t,    	setlayout,      {.v = &layouts[0] } },
	{ MODKEY,          	XK_b,    	setlayout,      {.v = &layouts[1] } },
	{ MODKEY,         	XK_m,  		setlayout,      {.v = &layouts[2] } },
	{ MODKEY,          	XK_f,   	setlayout,      {.v = &layouts[3] } },
	{ MODKEY,         	XK_Right, 	focusstack,     {.i = +1 } },
	{ MODKEY,         	XK_Left,  	focusstack,     {.i = -1 } },
	{ MODKEY,          	XK_h,      	setmfact,       {.f = -0.05 } },
	{ MODKEY,          	XK_l,      	setmfact,       {.f = +0.05 } },
	{ MODKEY,          	XK_equal,  	incnmaster,     {.i = +1 } },
	{ MODKEY,      		XK_minus,	incnmaster,     {.i = -1 } },
	{ MODKEY,        	XK_Down, 	focusstack, 	{.i = +1 } },
	{ MODKEY,         	XK_Up, 		focusstack,   	{.i = -1 } },
	{ MODKEY,        	XK_0,      	view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,	XK_0,      	tag,            {.ui = ~0 } },
	{ MODKEY,         	XK_comma, 	focusmon,       {.i = -1 } },
	{ MODKEY,        	XK_period,	focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,	XK_comma,  	tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,	XK_period, 	tagmon,         {.i = +1 } },
	TAGKEYS(        	XK_1,   	0)
	TAGKEYS(        	XK_2,   	1)
	TAGKEYS(        	XK_3,    	2)
	TAGKEYS(        	XK_4,   	3)
	TAGKEYS(          	XK_5,   	4)
	TAGKEYS(          	XK_6,   	5)
};

static Button buttons[] = {
	{ ClkClientWin,		MODKEY,  	Button1,        movemouse,      {0} },
	{ ClkClientWin,		MODKEY,   	Button2,        togglefloating, {0} },
	{ ClkClientWin,		MODKEY,    	Button3,        resizemouse,    {0} },
	{ ClkTagBar,  		0,       	Button1,        view,           {0} },
	{ ClkTagBar,  		0,         	Button3,        toggleview,     {0} },
	{ ClkTagBar, 		MODKEY,   	Button1,        tag,            {0} },
	{ ClkTagBar,  		MODKEY,   	Button3,        toggletag,      {0} },
};
