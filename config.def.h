/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const int gappx  	    = 0; 	/* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Noto Sans:size=11", "Material Design Icons:size=12", "Noto Color Emoji:size=11", "Noto Sans CJK KR:size=10" };

/* static const char *fonts[]          = { "monospace:size=11", "Material Design Icons:size=11", "Noto Color Emoji:pixelsize=11:antialias=true:autohint=true", "NanumGothicCoding:style=Bold:pixelsize=14:antialias=true:autohint=true" }; */

static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
static const char *tags[] = { "일", "이", "삼", "사", "오", "육", "칠", "팔", "구" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance    title       tags mask     iscentered   isfloating   monitor */
	{ "Gimp",     	 NULL,       NULL,       0,            0,           0,           -1 },
	{ "Firefox", 	 NULL,       NULL,       0,            0,           0,           -1 },
	{  NULL,  	 NULL,       "Spotify",  1<<8,         0,           0,            1 },
	{ "discord",  	 NULL,       NULL,       1<<7,         0,           0,            1 },
	{ "Pavucontrol", NULL,       NULL,       0,            1,           1,           -1 },
	{ "fcitx-config-gtk3", NULL, NULL,       0,            1,           1,           -1 },
	{ "flameshot", 	 NULL,       "Configuration", 0,       1,           1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

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
#define TERMINAL "st"

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
/* static const char *browsercmd[]  = { "firefox", NULL }; */
/* static const char *rsscmd[]  = { TERMINAL, "-e", "newsboat", NULL }; */
/* static const char *fmcmd[]  = { "nemo", NULL }; */
/* static const char *tfmcmd[]  = { TERMINAL, "-e", "ranger", NULL }; */
/* static const char *mailcmd[]  = { TERMINAL, "-e", "neomutt", "; pkill -RTMIN+12 dwmblocks", NULL }; */

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	/* { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } }, */
	{ MODKEY,	                XK_Return, spawn,          {.v = termcmd } },
	/* { MODKEY,	                XK_w,	   spawn,          {.v = browsercmd } }, */
	/* { MODKEY,			XK_r,	   spawn,	   {.v = fmcmd } }, */
	/* { MODKEY|ShiftMask,		XK_r,	   spawn,	   {.v = tfmcmd	} }, */
	/* { MODKEY,			XK_n,	   spawn,	   {.v = rsscmd } }, */
	/* { MODKEY,			XK_e,	   spawn,	   {.v = mailcmd } }, */


	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_period, setmfact,       {.f = +0.05} },
	{ MODKEY,	                XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask, 		XK_y,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[2]} },
	/* { MODKEY,                       XK_u,  setlayout,      {0} }, */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_h,  	   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_l, 	   focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,	   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,	   tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_BackSpace,      quit,           {0} },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
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
