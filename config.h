/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "serif:size=12" };
static const char dmenufont[]       = "sans:size=22";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";

/* My colors */
static const char col_white[]       = "#dadada";
static const char col_gray[]        = "#585858";
static const char col_darkgray[]    = "#444444";
static const char col_orange[]      = "#ff8787";
static const char col_magenta[]     = "#d75fff";
static const char col_olive[]       = "#afaf87";
static const char col_cyan[]        = "#5fafd7";
static const char col_red[]         = "#ff005f";
static const char col_pink[]        = "#af5f5f";
static const char col_green[]       = "#87d75f";

static const char *colors[][3]      = {
	/*               fg         bg            border   */
	[SchemeNorm] = { col_olive, col_darkgray, col_olive },
	[SchemeSel]  = { col_cyan,  col_gray,     col_magenta  },
};

/* tagging */
static const char *tags[] = { "$_", "ý", "://", "...", "@", "ⅵ", "▧", "&" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Utility",  NULL,       NULL,       0,            1,           -1 },
	{ "Yad",      NULL,       NULL,       0,            1,           -1 },
	{ "Zathura",  NULL,       NULL,       2,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const char *browsercmd[]           = { "firefox-developer-edition", NULL };
static const char *pingoutcmd[]           = { "st", "-c", "Utility", "-e", "ping", "-c", "16", "-v", "-w", "60", "to-ping", NULL };
static const char *ncmpcppcmd[]           = { "st", "-e", "ncmpcpp", NULL };

static const char *mute[]                 = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *volumedown[]           = { "amixer", "-q", "set", "Master", "2%-", "unmute", NULL };
static const char *volumeup[]             = { "amixer", "-q", "set", "Master", "2%+", "unmute", NULL };
static const char *playtoggle[]           = { "mpc", "toggle", NULL };
static const char *playnext[]             = { "mpc", "next", NULL };
static const char *playprev[]             = { "mpc", "prev", NULL };

static const char *brightnessup[]         = { "brightnessctl", "set", "2%+", NULL };
static const char *brightnessdown[]       = { "brightnessctl", "set", "2%-", NULL };

static const char *pwcmd[]                = { "pw.sh", NULL };
static const char *zopenmd[]              = { "zopen.sh", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },

	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_F5,     spawn,          {.v = zopenmd } },
	{ MODKEY,                       XK_F10,    spawn,          {.v = ncmpcppcmd } },
	{ MODKEY,                       XK_F12,    spawn,          {.v = pingoutcmd } },
	{ MODKEY,                       XK_Escape, spawn,          {.v = pwcmd } },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	// https://cgit.freedesktop.org/xorg/proto/x11proto/tree/XF86keysym.h
	#include <X11/XF86keysym.h>

	{ MODKEY,                       XK_F2,     spawn,          {.v = brightnessdown}},
	{ MODKEY,                       XK_F3,     spawn,          {.v = brightnessup}},

	{ 0,              XF86XK_AudioMute,        spawn,          {.v = mute}},
	{ 0,              XF86XK_AudioLowerVolume, spawn,          {.v = volumedown}},
	{ 0,              XF86XK_AudioRaiseVolume, spawn,          {.v = volumeup}},
	{ 0,              XF86XK_AudioPlay,        spawn,          {.v = playtoggle}},
	{ 0,              XF86XK_AudioNext,        spawn,          {.v = playnext}},
	{ 0,              XF86XK_AudioPrev,        spawn,          {.v = playprev}},

//#define XF86XK_RFKill		0x1008FFB5   /* Toggle radios on/off */

	/* moveresize patch bindings */
	{ MODKEY,				XK_Down,	moveresize,		{.v = (int []){ 0, 25, 0, 0 }}},
	{ MODKEY,				XK_Up,		moveresize,		{.v = (int []){ 0, -25, 0, 0 }}},
	{ MODKEY,				XK_Right,	moveresize,		{.v = (int []){ 25, 0, 0, 0 }}},
	{ MODKEY,				XK_Left,	moveresize,		{.v = (int []){ -25, 0, 0, 0 }}},
	{ MODKEY|ShiftMask,		XK_Down,	moveresize,		{.v = (int []){ 0, 0, 0, 25 }}},
	{ MODKEY|ShiftMask,		XK_Up,		moveresize,		{.v = (int []){ 0, 0, 0, -25 }}},
	{ MODKEY|ShiftMask,		XK_Right,	moveresize,		{.v = (int []){ 0, 0, 25, 0 }}},
	{ MODKEY|ShiftMask,		XK_Left,	moveresize,		{.v = (int []){ 0, 0, -25, 0 }}},

//	{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
//	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
//	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
//	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
//	{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
//	{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
//	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
//	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

