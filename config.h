/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int startwithgaps[]    = { 1 };	/* 1 means gaps are used by default, this can be customized for each tag */
static const unsigned int gappx[]   = { 10 };   /* default gap between windows in pixels, this can be customized for each tag */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "MonoLisa:size=12:pixelsize=15:antialias=true:autohint=true:style=Regular" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#101010";
static const char col_gray2[]       = "#454545";
static const char col_gray3[]       = "#999999";
static const char col_gray4[]       = "#b9b9b9";
static const char col_gray5[]       = "#252525";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray4, col_gray5, col_gray2 },
};

/* [[ Scratchpads Config ]] */
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
#include "alacritty.h"
// const char *spcmd1[] = {"st", "-n", "spterm", "-g", "134x31", NULL };
// const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "nnn", "-e",  NULL };
// const char *spcmd3[] = {"st", "-n", "spmail", "-g", "134x31", "-e", "neomutt", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spfm",		spcmd2},
	{"spmail",		spcmd3},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance      title		tags mask	isfloating	monitor */
	{ NULL,		  "spterm",	NULL,		SPTAG(0),	1,		-1 },
	{ NULL,		  "spfm",	NULL,		SPTAG(1),	1,		-1 },
	{ NULL,		  "spmail",	NULL,		SPTAG(2),	1,		-1 },
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
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include <X11/XF86keysym.h>
#include "movestack.c"
#include "shiftviewclients.c"
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-x", "650", "-y", "300", "-z", "700", "-l", "20", NULL };
// static const char *termcmd[]  = { "st", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browser[] = { "qutebrowser", NULL };
static const char *sysact[] = { "dmenu-exit", NULL };
static const char *lockcmd[] = { "lock", NULL };
static const char *scrot[] = { "scrot", NULL };
static const char *maimpick[] = { "maimpick", NULL };
static const char *screenrecord[] = { "dmenurecord", NULL };
static const char *volup[] = { "mcontrol", "up", NULL };
static const char *voldown[] = { "mcontrol", "down", NULL };
static const char *voltoggle[] = { "mcontrol", "toggle", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,						XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = browser } },
	// [[ Scratchpads ]]
	{ MODKEY|ShiftMask,				XK_Return, togglescratch,  {.ui = 0 } },
	{ MODKEY,						XK_e,	   togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,				XK_m,	   togglescratch,  {.ui = 2 } },
	// [[ End scratchpads]]
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,						XK_q,      killclient,     {0} },
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
	{ MODKEY,                       XK_z,	   setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_x,      setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	{ ControlMask,                  XK_Tab,	   shiftviewclients, {.i = +1} },
	{ ControlMask|ShiftMask,        XK_Tab,    shiftviewclients, {.i = -1} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,		quit,           {0} },
	{ MODKEY|ShiftMask,				XK_s,		spawn,          {.v = maimpick } },
	{ MODKEY|ShiftMask,				XK_r,		spawn,          {.v = screenrecord } },
	{ ControlMask|ALTKEY,			XK_Delete,		spawn,	{.v = sysact } },
	{ 0,				XF86XK_PowerOff,		spawn,	{.v = sysact} },
	{ MODKEY|ShiftMask,             XK_l,		spawn,          {.v = lockcmd } },
	{ 0,				XK_Print,				spawn,	{.v = scrot} },
// [[ Volume keys ]]
	{ 0,				XF86XK_AudioLowerVolume,		spawn,	{.v = voldown} },
	{ 0,				XF86XK_AudioRaiseVolume,		spawn,	{.v = volup} },
	{ 0,				XF86XK_AudioMute,				spawn,	{.v = voltoggle} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

