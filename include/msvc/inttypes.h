


<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
 <link rel="icon" type="image/vnd.microsoft.icon" href="http://www.gstatic.com/codesite/ph/images/phosting.ico">
 
 <script type="text/javascript">
 
 
 
 var codesite_token = null;
 
 
 var logged_in_user_email = null;
 
 
 var relative_base_url = "";
 
 </script>
 
 
 <title>inttypes.h - 
 baseutils -
 
 Project Hosting on Google Code</title>
 <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" >
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/11982002900633812604/css/ph_core.css">
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/11982002900633812604/css/ph_detail.css" >
 
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/11982002900633812604/css/d_sb_20080522.css" >
 
 
 
<!--[if IE]>
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/11982002900633812604/css/d_ie.css" >
<![endif]-->
 <style type="text/css">
 .menuIcon.off { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -42px }
 .menuIcon.on { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -28px }
 .menuIcon.down { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 0; }
 </style>
</head>
<body class="t4">
 <script type="text/javascript">
 var _gaq = _gaq || [];
 _gaq.push(
 ['siteTracker._setAccount', 'UA-18071-1'],
 ['siteTracker._trackPageview']);
 
 (function() {
 var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
 ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
 (document.getElementsByTagName('head')[0] || document.getElementsByTagName('body')[0]).appendChild(ga);
 })();
 </script>
 <div id="gaia">
 
 <span>
 
 
 <a href="#" id="projects-dropdown" onclick="return false;"><u>My favorites</u> <small>&#9660;</small></a>
 
 | <a href="https://www.google.com/accounts/ServiceLogin?service=code&amp;ltmpl=phosting&amp;continue=http%3A%2F%2Fcode.google.com%2Fp%2Fbaseutils%2Fsource%2Fbrowse%2Ftrunk%2Fmsvc%2Finttypes.h&amp;followup=http%3A%2F%2Fcode.google.com%2Fp%2Fbaseutils%2Fsource%2Fbrowse%2Ftrunk%2Fmsvc%2Finttypes.h" onclick="_CS_click('/gb/ph/signin');"><u>Sign in</u></a>
 
 </span>

 </div>
 <div class="gbh" style="left: 0pt;"></div>
 <div class="gbh" style="right: 0pt;"></div>
 
 
 <div style="height: 1px"></div>
<!--[if IE 6]>
<div style="text-align:center;">
Support browsers that contribute to open source, try <a href="http://www.firefox.com">Firefox</a> or <a href="http://www.google.com/chrome">Google Chrome</a>.
</div>
<![endif]-->



 <table style="padding:0px; margin: 20px 0px 0px 0px; width:100%" cellpadding="0" cellspacing="0">
 <tr style="height: 58px;">
 
 <td style="width: 55px; text-align:center;">
 <a href="/p/baseutils/">
 
 
 <img src="http://www.gstatic.com/codesite/ph/images/defaultlogo.png" alt="Logo">
 
 
 </a>
 </td>
 
 <td style="padding-left: 0.5em">
 
 <div id="pname" style="margin: 0px 0px -3px 0px">
 <a href="/p/baseutils/" style="text-decoration:none; color:#000">baseutils</a>
 
 </div>
 <div id="psum">
 <i><a id="project_summary_link" href="/p/baseutils/" style="text-decoration:none; color:#000">Basic, reusable code</a></i>
 </div>
 
 </td>
 <td style="white-space:nowrap;text-align:right">
 <form action="/hosting/search">
 <input size="30" name="q" value="">
 <input type="submit" name="projectsearch" value="Search projects" >
 </form>
 </tr>
 </table>


 
<table id="mt" cellspacing="0" cellpadding="0" width="100%" border="0">
 <tr>
 <th onclick="if (!cancelBubble) _go('/p/baseutils/');">
 <div class="tab inactive">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <a onclick="cancelBubble=true;" href="/p/baseutils/">Project&nbsp;Home</a>
 </div>
 </div>
 </th><td>&nbsp;&nbsp;</td>
 
 
 
 
 <th onclick="if (!cancelBubble) _go('/p/baseutils/downloads/list');">
 <div class="tab inactive">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <a onclick="cancelBubble=true;" href="/p/baseutils/downloads/list">Downloads</a>
 </div>
 </div>
 </th><td>&nbsp;&nbsp;</td>
 
 
 
 
 
 <th onclick="if (!cancelBubble) _go('/p/baseutils/w/list');">
 <div class="tab inactive">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <a onclick="cancelBubble=true;" href="/p/baseutils/w/list">Wiki</a>
 </div>
 </div>
 </th><td>&nbsp;&nbsp;</td>
 
 
 
 
 
 <th onclick="if (!cancelBubble) _go('/p/baseutils/issues/list');">
 <div class="tab inactive">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <a onclick="cancelBubble=true;" href="/p/baseutils/issues/list">Issues</a>
 </div>
 </div>
 </th><td>&nbsp;&nbsp;</td>
 
 
 
 
 
 <th onclick="if (!cancelBubble) _go('/p/baseutils/source/checkout');">
 <div class="tab active">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <a onclick="cancelBubble=true;" href="/p/baseutils/source/checkout">Source</a>
 </div>
 </div>
 </th><td>&nbsp;&nbsp;</td>
 
 
 <td width="100%">&nbsp;</td>
 </tr>
</table>
<table cellspacing="0" cellpadding="0" width="100%" align="center" border="0" class="st">
 <tr>
 
 
 
 
 
 
 <td>
 <div class="st2">
 <div class="isf">
 
 
 
 <span class="inst1"><a href="/p/baseutils/source/checkout">Checkout</a></span> |
 <span class="inst2"><a href="/p/baseutils/source/browse/">Browse</a></span> |
 <span class="inst3"><a href="/p/baseutils/source/list">Changes</a></span> |
 
 <form action="http://www.google.com/codesearch" method="get" style="display:inline"
 onsubmit="document.getElementById('codesearchq').value = document.getElementById('origq').value + ' package:http://baseutils\\.googlecode\\.com'">
 <input type="hidden" name="q" id="codesearchq" value="">
 <input maxlength="2048" size="38" id="origq" name="origq" value="" title="Google Code Search" style="font-size:92%">&nbsp;<input type="submit" value="Search Trunk" name="btnG" style="font-size:92%">
 
 
 
 </form>
 </div>
</div>

 </td>
 
 
 
 <td height="4" align="right" valign="top" class="bevel-right">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 </td>
 </tr>
</table>
<script type="text/javascript">
 var cancelBubble = false;
 function _go(url) { document.location = url; }
</script>


<div id="maincol"
 
>

 
<!-- IE -->




<div class="expand">


<style type="text/css">
 #file_flipper { display: inline; float: right; white-space: nowrap; }
 #file_flipper.hidden { display: none; }
 #file_flipper .pagelink { color: #0000CC; text-decoration: underline; }
 #file_flipper #visiblefiles { padding-left: 0.5em; padding-right: 0.5em; }
</style>
<div id="nav_and_rev" class="heading">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner" id="bub">
 <div class="bub-top">
 <div class="pagination" style="margin-left: 2em">
 <table cellpadding="0" cellspacing="0" class="flipper">
 <tbody>
 <tr>
 
 <td><b>r106</b></td>
 
 </tr>
 </tbody>
 </table>
 </div>
 
 <div class="" style="vertical-align: top">
 <div class="src_crumbs src_nav">
 <strong class="src_nav">Source path:&nbsp;</strong>
 <span id="crumb_root">
 
 <a href="/p/baseutils/source/browse/">svn</a>/&nbsp;</span>
 <span id="crumb_links" class="ifClosed"><a href="/p/baseutils/source/browse/trunk/">trunk</a><span class="sp">/&nbsp;</span><a href="/p/baseutils/source/browse/trunk/msvc/">msvc</a><span class="sp">/&nbsp;</span>inttypes.h</span>
 
 
 </div>
 
 </div>
 <div style="clear:both"></div>
 </div>
 </div>
</div>

<style type="text/css">
 
  tr.inline_comment {
 background: #fff;
 vertical-align: top;
 }
 div.draft, div.published {
 padding: .3em;
 border: 1px solid #999; 
 margin-bottom: .1em;
 font-family: arial, sans-serif;
 max-width: 60em;
 }
 div.draft {
 background: #ffa;
 } 
 div.published {
 background: #e5ecf9;
 }
 div.published .body, div.draft .body {
 padding: .5em .1em .1em .1em;
 max-width: 60em;
 white-space: pre-wrap;
 white-space: -moz-pre-wrap;
 white-space: -pre-wrap;
 white-space: -o-pre-wrap;
 word-wrap: break-word;
 }
 div.draft .actions {
 margin-left: 1em;
 font-size: 90%;
 }
 div.draft form {
 padding: .5em .5em .5em 0;
 }
 div.draft textarea, div.published textarea {
 width: 95%;
 height: 10em;
 font-family: arial, sans-serif;
 margin-bottom: .5em;
 }


 
 .nocursor, .nocursor td, .cursor_hidden, .cursor_hidden td {
 background-color: white;
 height: 2px;
 }
 .cursor, .cursor td {
 background-color: darkblue;
 height: 2px;
 display: '';
 }

</style>
<div class="fc">
 


<table class="opened" id="review_comment_area"><tr>
<td id="nums">
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>

<pre><table width="100%"><tr id="gr_svn55_1"><td id="1"><a href="#1">1</a></td></tr
><tr id="gr_svn55_2"><td id="2"><a href="#2">2</a></td></tr
><tr id="gr_svn55_3"><td id="3"><a href="#3">3</a></td></tr
><tr id="gr_svn55_4"><td id="4"><a href="#4">4</a></td></tr
><tr id="gr_svn55_5"><td id="5"><a href="#5">5</a></td></tr
><tr id="gr_svn55_6"><td id="6"><a href="#6">6</a></td></tr
><tr id="gr_svn55_7"><td id="7"><a href="#7">7</a></td></tr
><tr id="gr_svn55_8"><td id="8"><a href="#8">8</a></td></tr
><tr id="gr_svn55_9"><td id="9"><a href="#9">9</a></td></tr
><tr id="gr_svn55_10"><td id="10"><a href="#10">10</a></td></tr
><tr id="gr_svn55_11"><td id="11"><a href="#11">11</a></td></tr
><tr id="gr_svn55_12"><td id="12"><a href="#12">12</a></td></tr
><tr id="gr_svn55_13"><td id="13"><a href="#13">13</a></td></tr
><tr id="gr_svn55_14"><td id="14"><a href="#14">14</a></td></tr
><tr id="gr_svn55_15"><td id="15"><a href="#15">15</a></td></tr
><tr id="gr_svn55_16"><td id="16"><a href="#16">16</a></td></tr
><tr id="gr_svn55_17"><td id="17"><a href="#17">17</a></td></tr
><tr id="gr_svn55_18"><td id="18"><a href="#18">18</a></td></tr
><tr id="gr_svn55_19"><td id="19"><a href="#19">19</a></td></tr
><tr id="gr_svn55_20"><td id="20"><a href="#20">20</a></td></tr
><tr id="gr_svn55_21"><td id="21"><a href="#21">21</a></td></tr
><tr id="gr_svn55_22"><td id="22"><a href="#22">22</a></td></tr
><tr id="gr_svn55_23"><td id="23"><a href="#23">23</a></td></tr
><tr id="gr_svn55_24"><td id="24"><a href="#24">24</a></td></tr
><tr id="gr_svn55_25"><td id="25"><a href="#25">25</a></td></tr
><tr id="gr_svn55_26"><td id="26"><a href="#26">26</a></td></tr
><tr id="gr_svn55_27"><td id="27"><a href="#27">27</a></td></tr
><tr id="gr_svn55_28"><td id="28"><a href="#28">28</a></td></tr
><tr id="gr_svn55_29"><td id="29"><a href="#29">29</a></td></tr
><tr id="gr_svn55_30"><td id="30"><a href="#30">30</a></td></tr
><tr id="gr_svn55_31"><td id="31"><a href="#31">31</a></td></tr
><tr id="gr_svn55_32"><td id="32"><a href="#32">32</a></td></tr
><tr id="gr_svn55_33"><td id="33"><a href="#33">33</a></td></tr
><tr id="gr_svn55_34"><td id="34"><a href="#34">34</a></td></tr
><tr id="gr_svn55_35"><td id="35"><a href="#35">35</a></td></tr
><tr id="gr_svn55_36"><td id="36"><a href="#36">36</a></td></tr
><tr id="gr_svn55_37"><td id="37"><a href="#37">37</a></td></tr
><tr id="gr_svn55_38"><td id="38"><a href="#38">38</a></td></tr
><tr id="gr_svn55_39"><td id="39"><a href="#39">39</a></td></tr
><tr id="gr_svn55_40"><td id="40"><a href="#40">40</a></td></tr
><tr id="gr_svn55_41"><td id="41"><a href="#41">41</a></td></tr
><tr id="gr_svn55_42"><td id="42"><a href="#42">42</a></td></tr
><tr id="gr_svn55_43"><td id="43"><a href="#43">43</a></td></tr
><tr id="gr_svn55_44"><td id="44"><a href="#44">44</a></td></tr
><tr id="gr_svn55_45"><td id="45"><a href="#45">45</a></td></tr
><tr id="gr_svn55_46"><td id="46"><a href="#46">46</a></td></tr
><tr id="gr_svn55_47"><td id="47"><a href="#47">47</a></td></tr
><tr id="gr_svn55_48"><td id="48"><a href="#48">48</a></td></tr
><tr id="gr_svn55_49"><td id="49"><a href="#49">49</a></td></tr
><tr id="gr_svn55_50"><td id="50"><a href="#50">50</a></td></tr
><tr id="gr_svn55_51"><td id="51"><a href="#51">51</a></td></tr
><tr id="gr_svn55_52"><td id="52"><a href="#52">52</a></td></tr
><tr id="gr_svn55_53"><td id="53"><a href="#53">53</a></td></tr
><tr id="gr_svn55_54"><td id="54"><a href="#54">54</a></td></tr
><tr id="gr_svn55_55"><td id="55"><a href="#55">55</a></td></tr
><tr id="gr_svn55_56"><td id="56"><a href="#56">56</a></td></tr
><tr id="gr_svn55_57"><td id="57"><a href="#57">57</a></td></tr
><tr id="gr_svn55_58"><td id="58"><a href="#58">58</a></td></tr
><tr id="gr_svn55_59"><td id="59"><a href="#59">59</a></td></tr
><tr id="gr_svn55_60"><td id="60"><a href="#60">60</a></td></tr
><tr id="gr_svn55_61"><td id="61"><a href="#61">61</a></td></tr
><tr id="gr_svn55_62"><td id="62"><a href="#62">62</a></td></tr
><tr id="gr_svn55_63"><td id="63"><a href="#63">63</a></td></tr
><tr id="gr_svn55_64"><td id="64"><a href="#64">64</a></td></tr
><tr id="gr_svn55_65"><td id="65"><a href="#65">65</a></td></tr
><tr id="gr_svn55_66"><td id="66"><a href="#66">66</a></td></tr
><tr id="gr_svn55_67"><td id="67"><a href="#67">67</a></td></tr
><tr id="gr_svn55_68"><td id="68"><a href="#68">68</a></td></tr
><tr id="gr_svn55_69"><td id="69"><a href="#69">69</a></td></tr
><tr id="gr_svn55_70"><td id="70"><a href="#70">70</a></td></tr
><tr id="gr_svn55_71"><td id="71"><a href="#71">71</a></td></tr
><tr id="gr_svn55_72"><td id="72"><a href="#72">72</a></td></tr
><tr id="gr_svn55_73"><td id="73"><a href="#73">73</a></td></tr
><tr id="gr_svn55_74"><td id="74"><a href="#74">74</a></td></tr
><tr id="gr_svn55_75"><td id="75"><a href="#75">75</a></td></tr
><tr id="gr_svn55_76"><td id="76"><a href="#76">76</a></td></tr
><tr id="gr_svn55_77"><td id="77"><a href="#77">77</a></td></tr
><tr id="gr_svn55_78"><td id="78"><a href="#78">78</a></td></tr
><tr id="gr_svn55_79"><td id="79"><a href="#79">79</a></td></tr
><tr id="gr_svn55_80"><td id="80"><a href="#80">80</a></td></tr
><tr id="gr_svn55_81"><td id="81"><a href="#81">81</a></td></tr
><tr id="gr_svn55_82"><td id="82"><a href="#82">82</a></td></tr
><tr id="gr_svn55_83"><td id="83"><a href="#83">83</a></td></tr
><tr id="gr_svn55_84"><td id="84"><a href="#84">84</a></td></tr
><tr id="gr_svn55_85"><td id="85"><a href="#85">85</a></td></tr
><tr id="gr_svn55_86"><td id="86"><a href="#86">86</a></td></tr
><tr id="gr_svn55_87"><td id="87"><a href="#87">87</a></td></tr
><tr id="gr_svn55_88"><td id="88"><a href="#88">88</a></td></tr
><tr id="gr_svn55_89"><td id="89"><a href="#89">89</a></td></tr
><tr id="gr_svn55_90"><td id="90"><a href="#90">90</a></td></tr
><tr id="gr_svn55_91"><td id="91"><a href="#91">91</a></td></tr
><tr id="gr_svn55_92"><td id="92"><a href="#92">92</a></td></tr
><tr id="gr_svn55_93"><td id="93"><a href="#93">93</a></td></tr
><tr id="gr_svn55_94"><td id="94"><a href="#94">94</a></td></tr
><tr id="gr_svn55_95"><td id="95"><a href="#95">95</a></td></tr
><tr id="gr_svn55_96"><td id="96"><a href="#96">96</a></td></tr
><tr id="gr_svn55_97"><td id="97"><a href="#97">97</a></td></tr
><tr id="gr_svn55_98"><td id="98"><a href="#98">98</a></td></tr
><tr id="gr_svn55_99"><td id="99"><a href="#99">99</a></td></tr
><tr id="gr_svn55_100"><td id="100"><a href="#100">100</a></td></tr
><tr id="gr_svn55_101"><td id="101"><a href="#101">101</a></td></tr
><tr id="gr_svn55_102"><td id="102"><a href="#102">102</a></td></tr
><tr id="gr_svn55_103"><td id="103"><a href="#103">103</a></td></tr
><tr id="gr_svn55_104"><td id="104"><a href="#104">104</a></td></tr
><tr id="gr_svn55_105"><td id="105"><a href="#105">105</a></td></tr
><tr id="gr_svn55_106"><td id="106"><a href="#106">106</a></td></tr
><tr id="gr_svn55_107"><td id="107"><a href="#107">107</a></td></tr
><tr id="gr_svn55_108"><td id="108"><a href="#108">108</a></td></tr
><tr id="gr_svn55_109"><td id="109"><a href="#109">109</a></td></tr
><tr id="gr_svn55_110"><td id="110"><a href="#110">110</a></td></tr
><tr id="gr_svn55_111"><td id="111"><a href="#111">111</a></td></tr
><tr id="gr_svn55_112"><td id="112"><a href="#112">112</a></td></tr
><tr id="gr_svn55_113"><td id="113"><a href="#113">113</a></td></tr
><tr id="gr_svn55_114"><td id="114"><a href="#114">114</a></td></tr
><tr id="gr_svn55_115"><td id="115"><a href="#115">115</a></td></tr
><tr id="gr_svn55_116"><td id="116"><a href="#116">116</a></td></tr
><tr id="gr_svn55_117"><td id="117"><a href="#117">117</a></td></tr
><tr id="gr_svn55_118"><td id="118"><a href="#118">118</a></td></tr
><tr id="gr_svn55_119"><td id="119"><a href="#119">119</a></td></tr
><tr id="gr_svn55_120"><td id="120"><a href="#120">120</a></td></tr
><tr id="gr_svn55_121"><td id="121"><a href="#121">121</a></td></tr
><tr id="gr_svn55_122"><td id="122"><a href="#122">122</a></td></tr
><tr id="gr_svn55_123"><td id="123"><a href="#123">123</a></td></tr
><tr id="gr_svn55_124"><td id="124"><a href="#124">124</a></td></tr
><tr id="gr_svn55_125"><td id="125"><a href="#125">125</a></td></tr
><tr id="gr_svn55_126"><td id="126"><a href="#126">126</a></td></tr
><tr id="gr_svn55_127"><td id="127"><a href="#127">127</a></td></tr
><tr id="gr_svn55_128"><td id="128"><a href="#128">128</a></td></tr
><tr id="gr_svn55_129"><td id="129"><a href="#129">129</a></td></tr
><tr id="gr_svn55_130"><td id="130"><a href="#130">130</a></td></tr
><tr id="gr_svn55_131"><td id="131"><a href="#131">131</a></td></tr
><tr id="gr_svn55_132"><td id="132"><a href="#132">132</a></td></tr
><tr id="gr_svn55_133"><td id="133"><a href="#133">133</a></td></tr
><tr id="gr_svn55_134"><td id="134"><a href="#134">134</a></td></tr
><tr id="gr_svn55_135"><td id="135"><a href="#135">135</a></td></tr
><tr id="gr_svn55_136"><td id="136"><a href="#136">136</a></td></tr
><tr id="gr_svn55_137"><td id="137"><a href="#137">137</a></td></tr
><tr id="gr_svn55_138"><td id="138"><a href="#138">138</a></td></tr
><tr id="gr_svn55_139"><td id="139"><a href="#139">139</a></td></tr
><tr id="gr_svn55_140"><td id="140"><a href="#140">140</a></td></tr
><tr id="gr_svn55_141"><td id="141"><a href="#141">141</a></td></tr
><tr id="gr_svn55_142"><td id="142"><a href="#142">142</a></td></tr
><tr id="gr_svn55_143"><td id="143"><a href="#143">143</a></td></tr
><tr id="gr_svn55_144"><td id="144"><a href="#144">144</a></td></tr
><tr id="gr_svn55_145"><td id="145"><a href="#145">145</a></td></tr
><tr id="gr_svn55_146"><td id="146"><a href="#146">146</a></td></tr
><tr id="gr_svn55_147"><td id="147"><a href="#147">147</a></td></tr
><tr id="gr_svn55_148"><td id="148"><a href="#148">148</a></td></tr
><tr id="gr_svn55_149"><td id="149"><a href="#149">149</a></td></tr
><tr id="gr_svn55_150"><td id="150"><a href="#150">150</a></td></tr
><tr id="gr_svn55_151"><td id="151"><a href="#151">151</a></td></tr
><tr id="gr_svn55_152"><td id="152"><a href="#152">152</a></td></tr
><tr id="gr_svn55_153"><td id="153"><a href="#153">153</a></td></tr
><tr id="gr_svn55_154"><td id="154"><a href="#154">154</a></td></tr
><tr id="gr_svn55_155"><td id="155"><a href="#155">155</a></td></tr
><tr id="gr_svn55_156"><td id="156"><a href="#156">156</a></td></tr
><tr id="gr_svn55_157"><td id="157"><a href="#157">157</a></td></tr
><tr id="gr_svn55_158"><td id="158"><a href="#158">158</a></td></tr
><tr id="gr_svn55_159"><td id="159"><a href="#159">159</a></td></tr
><tr id="gr_svn55_160"><td id="160"><a href="#160">160</a></td></tr
><tr id="gr_svn55_161"><td id="161"><a href="#161">161</a></td></tr
><tr id="gr_svn55_162"><td id="162"><a href="#162">162</a></td></tr
><tr id="gr_svn55_163"><td id="163"><a href="#163">163</a></td></tr
><tr id="gr_svn55_164"><td id="164"><a href="#164">164</a></td></tr
><tr id="gr_svn55_165"><td id="165"><a href="#165">165</a></td></tr
><tr id="gr_svn55_166"><td id="166"><a href="#166">166</a></td></tr
><tr id="gr_svn55_167"><td id="167"><a href="#167">167</a></td></tr
><tr id="gr_svn55_168"><td id="168"><a href="#168">168</a></td></tr
><tr id="gr_svn55_169"><td id="169"><a href="#169">169</a></td></tr
><tr id="gr_svn55_170"><td id="170"><a href="#170">170</a></td></tr
><tr id="gr_svn55_171"><td id="171"><a href="#171">171</a></td></tr
><tr id="gr_svn55_172"><td id="172"><a href="#172">172</a></td></tr
><tr id="gr_svn55_173"><td id="173"><a href="#173">173</a></td></tr
><tr id="gr_svn55_174"><td id="174"><a href="#174">174</a></td></tr
><tr id="gr_svn55_175"><td id="175"><a href="#175">175</a></td></tr
><tr id="gr_svn55_176"><td id="176"><a href="#176">176</a></td></tr
><tr id="gr_svn55_177"><td id="177"><a href="#177">177</a></td></tr
><tr id="gr_svn55_178"><td id="178"><a href="#178">178</a></td></tr
><tr id="gr_svn55_179"><td id="179"><a href="#179">179</a></td></tr
><tr id="gr_svn55_180"><td id="180"><a href="#180">180</a></td></tr
><tr id="gr_svn55_181"><td id="181"><a href="#181">181</a></td></tr
><tr id="gr_svn55_182"><td id="182"><a href="#182">182</a></td></tr
><tr id="gr_svn55_183"><td id="183"><a href="#183">183</a></td></tr
><tr id="gr_svn55_184"><td id="184"><a href="#184">184</a></td></tr
><tr id="gr_svn55_185"><td id="185"><a href="#185">185</a></td></tr
><tr id="gr_svn55_186"><td id="186"><a href="#186">186</a></td></tr
><tr id="gr_svn55_187"><td id="187"><a href="#187">187</a></td></tr
><tr id="gr_svn55_188"><td id="188"><a href="#188">188</a></td></tr
><tr id="gr_svn55_189"><td id="189"><a href="#189">189</a></td></tr
><tr id="gr_svn55_190"><td id="190"><a href="#190">190</a></td></tr
><tr id="gr_svn55_191"><td id="191"><a href="#191">191</a></td></tr
><tr id="gr_svn55_192"><td id="192"><a href="#192">192</a></td></tr
><tr id="gr_svn55_193"><td id="193"><a href="#193">193</a></td></tr
><tr id="gr_svn55_194"><td id="194"><a href="#194">194</a></td></tr
><tr id="gr_svn55_195"><td id="195"><a href="#195">195</a></td></tr
><tr id="gr_svn55_196"><td id="196"><a href="#196">196</a></td></tr
><tr id="gr_svn55_197"><td id="197"><a href="#197">197</a></td></tr
><tr id="gr_svn55_198"><td id="198"><a href="#198">198</a></td></tr
><tr id="gr_svn55_199"><td id="199"><a href="#199">199</a></td></tr
><tr id="gr_svn55_200"><td id="200"><a href="#200">200</a></td></tr
><tr id="gr_svn55_201"><td id="201"><a href="#201">201</a></td></tr
><tr id="gr_svn55_202"><td id="202"><a href="#202">202</a></td></tr
><tr id="gr_svn55_203"><td id="203"><a href="#203">203</a></td></tr
><tr id="gr_svn55_204"><td id="204"><a href="#204">204</a></td></tr
></table></pre>

<pre><table width="100%"><tr id="gr_svn55_205"><td id="205"><a href="#205">205</a></td></tr
><tr id="gr_svn55_206"><td id="206"><a href="#206">206</a></td></tr
><tr id="gr_svn55_207"><td id="207"><a href="#207">207</a></td></tr
><tr id="gr_svn55_208"><td id="208"><a href="#208">208</a></td></tr
><tr id="gr_svn55_209"><td id="209"><a href="#209">209</a></td></tr
><tr id="gr_svn55_210"><td id="210"><a href="#210">210</a></td></tr
><tr id="gr_svn55_211"><td id="211"><a href="#211">211</a></td></tr
><tr id="gr_svn55_212"><td id="212"><a href="#212">212</a></td></tr
><tr id="gr_svn55_213"><td id="213"><a href="#213">213</a></td></tr
><tr id="gr_svn55_214"><td id="214"><a href="#214">214</a></td></tr
><tr id="gr_svn55_215"><td id="215"><a href="#215">215</a></td></tr
><tr id="gr_svn55_216"><td id="216"><a href="#216">216</a></td></tr
><tr id="gr_svn55_217"><td id="217"><a href="#217">217</a></td></tr
><tr id="gr_svn55_218"><td id="218"><a href="#218">218</a></td></tr
><tr id="gr_svn55_219"><td id="219"><a href="#219">219</a></td></tr
><tr id="gr_svn55_220"><td id="220"><a href="#220">220</a></td></tr
><tr id="gr_svn55_221"><td id="221"><a href="#221">221</a></td></tr
><tr id="gr_svn55_222"><td id="222"><a href="#222">222</a></td></tr
><tr id="gr_svn55_223"><td id="223"><a href="#223">223</a></td></tr
><tr id="gr_svn55_224"><td id="224"><a href="#224">224</a></td></tr
><tr id="gr_svn55_225"><td id="225"><a href="#225">225</a></td></tr
><tr id="gr_svn55_226"><td id="226"><a href="#226">226</a></td></tr
><tr id="gr_svn55_227"><td id="227"><a href="#227">227</a></td></tr
><tr id="gr_svn55_228"><td id="228"><a href="#228">228</a></td></tr
><tr id="gr_svn55_229"><td id="229"><a href="#229">229</a></td></tr
><tr id="gr_svn55_230"><td id="230"><a href="#230">230</a></td></tr
><tr id="gr_svn55_231"><td id="231"><a href="#231">231</a></td></tr
><tr id="gr_svn55_232"><td id="232"><a href="#232">232</a></td></tr
><tr id="gr_svn55_233"><td id="233"><a href="#233">233</a></td></tr
><tr id="gr_svn55_234"><td id="234"><a href="#234">234</a></td></tr
><tr id="gr_svn55_235"><td id="235"><a href="#235">235</a></td></tr
><tr id="gr_svn55_236"><td id="236"><a href="#236">236</a></td></tr
><tr id="gr_svn55_237"><td id="237"><a href="#237">237</a></td></tr
><tr id="gr_svn55_238"><td id="238"><a href="#238">238</a></td></tr
><tr id="gr_svn55_239"><td id="239"><a href="#239">239</a></td></tr
><tr id="gr_svn55_240"><td id="240"><a href="#240">240</a></td></tr
><tr id="gr_svn55_241"><td id="241"><a href="#241">241</a></td></tr
><tr id="gr_svn55_242"><td id="242"><a href="#242">242</a></td></tr
><tr id="gr_svn55_243"><td id="243"><a href="#243">243</a></td></tr
><tr id="gr_svn55_244"><td id="244"><a href="#244">244</a></td></tr
><tr id="gr_svn55_245"><td id="245"><a href="#245">245</a></td></tr
><tr id="gr_svn55_246"><td id="246"><a href="#246">246</a></td></tr
><tr id="gr_svn55_247"><td id="247"><a href="#247">247</a></td></tr
><tr id="gr_svn55_248"><td id="248"><a href="#248">248</a></td></tr
><tr id="gr_svn55_249"><td id="249"><a href="#249">249</a></td></tr
><tr id="gr_svn55_250"><td id="250"><a href="#250">250</a></td></tr
><tr id="gr_svn55_251"><td id="251"><a href="#251">251</a></td></tr
><tr id="gr_svn55_252"><td id="252"><a href="#252">252</a></td></tr
><tr id="gr_svn55_253"><td id="253"><a href="#253">253</a></td></tr
><tr id="gr_svn55_254"><td id="254"><a href="#254">254</a></td></tr
><tr id="gr_svn55_255"><td id="255"><a href="#255">255</a></td></tr
><tr id="gr_svn55_256"><td id="256"><a href="#256">256</a></td></tr
><tr id="gr_svn55_257"><td id="257"><a href="#257">257</a></td></tr
><tr id="gr_svn55_258"><td id="258"><a href="#258">258</a></td></tr
><tr id="gr_svn55_259"><td id="259"><a href="#259">259</a></td></tr
><tr id="gr_svn55_260"><td id="260"><a href="#260">260</a></td></tr
><tr id="gr_svn55_261"><td id="261"><a href="#261">261</a></td></tr
><tr id="gr_svn55_262"><td id="262"><a href="#262">262</a></td></tr
><tr id="gr_svn55_263"><td id="263"><a href="#263">263</a></td></tr
><tr id="gr_svn55_264"><td id="264"><a href="#264">264</a></td></tr
><tr id="gr_svn55_265"><td id="265"><a href="#265">265</a></td></tr
><tr id="gr_svn55_266"><td id="266"><a href="#266">266</a></td></tr
><tr id="gr_svn55_267"><td id="267"><a href="#267">267</a></td></tr
><tr id="gr_svn55_268"><td id="268"><a href="#268">268</a></td></tr
><tr id="gr_svn55_269"><td id="269"><a href="#269">269</a></td></tr
><tr id="gr_svn55_270"><td id="270"><a href="#270">270</a></td></tr
><tr id="gr_svn55_271"><td id="271"><a href="#271">271</a></td></tr
><tr id="gr_svn55_272"><td id="272"><a href="#272">272</a></td></tr
><tr id="gr_svn55_273"><td id="273"><a href="#273">273</a></td></tr
><tr id="gr_svn55_274"><td id="274"><a href="#274">274</a></td></tr
><tr id="gr_svn55_275"><td id="275"><a href="#275">275</a></td></tr
><tr id="gr_svn55_276"><td id="276"><a href="#276">276</a></td></tr
><tr id="gr_svn55_277"><td id="277"><a href="#277">277</a></td></tr
><tr id="gr_svn55_278"><td id="278"><a href="#278">278</a></td></tr
><tr id="gr_svn55_279"><td id="279"><a href="#279">279</a></td></tr
><tr id="gr_svn55_280"><td id="280"><a href="#280">280</a></td></tr
><tr id="gr_svn55_281"><td id="281"><a href="#281">281</a></td></tr
><tr id="gr_svn55_282"><td id="282"><a href="#282">282</a></td></tr
><tr id="gr_svn55_283"><td id="283"><a href="#283">283</a></td></tr
><tr id="gr_svn55_284"><td id="284"><a href="#284">284</a></td></tr
><tr id="gr_svn55_285"><td id="285"><a href="#285">285</a></td></tr
><tr id="gr_svn55_286"><td id="286"><a href="#286">286</a></td></tr
><tr id="gr_svn55_287"><td id="287"><a href="#287">287</a></td></tr
><tr id="gr_svn55_288"><td id="288"><a href="#288">288</a></td></tr
><tr id="gr_svn55_289"><td id="289"><a href="#289">289</a></td></tr
><tr id="gr_svn55_290"><td id="290"><a href="#290">290</a></td></tr
><tr id="gr_svn55_291"><td id="291"><a href="#291">291</a></td></tr
><tr id="gr_svn55_292"><td id="292"><a href="#292">292</a></td></tr
><tr id="gr_svn55_293"><td id="293"><a href="#293">293</a></td></tr
><tr id="gr_svn55_294"><td id="294"><a href="#294">294</a></td></tr
><tr id="gr_svn55_295"><td id="295"><a href="#295">295</a></td></tr
><tr id="gr_svn55_296"><td id="296"><a href="#296">296</a></td></tr
><tr id="gr_svn55_297"><td id="297"><a href="#297">297</a></td></tr
><tr id="gr_svn55_298"><td id="298"><a href="#298">298</a></td></tr
><tr id="gr_svn55_299"><td id="299"><a href="#299">299</a></td></tr
><tr id="gr_svn55_300"><td id="300"><a href="#300">300</a></td></tr
><tr id="gr_svn55_301"><td id="301"><a href="#301">301</a></td></tr
></table></pre>

<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
</td>
<td id="lines">
<pre class="prettyprint"><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>

<pre class="prettyprint "><table><tr
id=sl_svn55_1><td class="source">// ISO C9x  compliant inttypes.h for Microsoft Visual Studio<br></td></tr
><tr
id=sl_svn55_2><td class="source">// Based on ISO/IEC 9899:TC2 Committee draft (May 6, 2005) WG14/N1124 <br></td></tr
><tr
id=sl_svn55_3><td class="source">// <br></td></tr
><tr
id=sl_svn55_4><td class="source">//  Copyright (c) 2006 Alexander Chemeris<br></td></tr
><tr
id=sl_svn55_5><td class="source">// <br></td></tr
><tr
id=sl_svn55_6><td class="source">// Redistribution and use in source and binary forms, with or without<br></td></tr
><tr
id=sl_svn55_7><td class="source">// modification, are permitted provided that the following conditions are met:<br></td></tr
><tr
id=sl_svn55_8><td class="source">// <br></td></tr
><tr
id=sl_svn55_9><td class="source">//   1. Redistributions of source code must retain the above copyright notice,<br></td></tr
><tr
id=sl_svn55_10><td class="source">//      this list of conditions and the following disclaimer.<br></td></tr
><tr
id=sl_svn55_11><td class="source">// <br></td></tr
><tr
id=sl_svn55_12><td class="source">//   2. Redistributions in binary form must reproduce the above copyright<br></td></tr
><tr
id=sl_svn55_13><td class="source">//      notice, this list of conditions and the following disclaimer in the<br></td></tr
><tr
id=sl_svn55_14><td class="source">//      documentation and/or other materials provided with the distribution.<br></td></tr
><tr
id=sl_svn55_15><td class="source">// <br></td></tr
><tr
id=sl_svn55_16><td class="source">//   3. The name of the author may be used to endorse or promote products<br></td></tr
><tr
id=sl_svn55_17><td class="source">//      derived from this software without specific prior written permission.<br></td></tr
><tr
id=sl_svn55_18><td class="source">// <br></td></tr
><tr
id=sl_svn55_19><td class="source">// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS&#39;&#39; AND ANY EXPRESS OR IMPLIED<br></td></tr
><tr
id=sl_svn55_20><td class="source">// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF<br></td></tr
><tr
id=sl_svn55_21><td class="source">// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO<br></td></tr
><tr
id=sl_svn55_22><td class="source">// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,<br></td></tr
><tr
id=sl_svn55_23><td class="source">// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,<br></td></tr
><tr
id=sl_svn55_24><td class="source">// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;<br></td></tr
><tr
id=sl_svn55_25><td class="source">// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, <br></td></tr
><tr
id=sl_svn55_26><td class="source">// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR<br></td></tr
><tr
id=sl_svn55_27><td class="source">// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF<br></td></tr
><tr
id=sl_svn55_28><td class="source">// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.<br></td></tr
><tr
id=sl_svn55_29><td class="source">// <br></td></tr
><tr
id=sl_svn55_30><td class="source">///////////////////////////////////////////////////////////////////////////////<br></td></tr
><tr
id=sl_svn55_31><td class="source"><br></td></tr
><tr
id=sl_svn55_32><td class="source">#ifndef _MSC_VER // [<br></td></tr
><tr
id=sl_svn55_33><td class="source">#error &quot;Use this header only with Microsoft Visual C++ compilers!&quot;<br></td></tr
><tr
id=sl_svn55_34><td class="source">#endif // _MSC_VER ]<br></td></tr
><tr
id=sl_svn55_35><td class="source"><br></td></tr
><tr
id=sl_svn55_36><td class="source">#ifndef _MSC_INTTYPES_H_ // [<br></td></tr
><tr
id=sl_svn55_37><td class="source">#define _MSC_INTTYPES_H_<br></td></tr
><tr
id=sl_svn55_38><td class="source"><br></td></tr
><tr
id=sl_svn55_39><td class="source">#if _MSC_VER &gt; 1000<br></td></tr
><tr
id=sl_svn55_40><td class="source">#pragma once<br></td></tr
><tr
id=sl_svn55_41><td class="source">#endif<br></td></tr
><tr
id=sl_svn55_42><td class="source"><br></td></tr
><tr
id=sl_svn55_43><td class="source">#include &lt;stdint.h&gt;<br></td></tr
><tr
id=sl_svn55_44><td class="source"><br></td></tr
><tr
id=sl_svn55_45><td class="source">// 7.8 Format conversion of integer types<br></td></tr
><tr
id=sl_svn55_46><td class="source"><br></td></tr
><tr
id=sl_svn55_47><td class="source">typedef struct {<br></td></tr
><tr
id=sl_svn55_48><td class="source">   intmax_t quot;<br></td></tr
><tr
id=sl_svn55_49><td class="source">   intmax_t rem;<br></td></tr
><tr
id=sl_svn55_50><td class="source">} imaxdiv_t;<br></td></tr
><tr
id=sl_svn55_51><td class="source"><br></td></tr
><tr
id=sl_svn55_52><td class="source">// 7.8.1 Macros for format specifiers<br></td></tr
><tr
id=sl_svn55_53><td class="source"><br></td></tr
><tr
id=sl_svn55_54><td class="source">// The fprintf macros for signed integers are:<br></td></tr
><tr
id=sl_svn55_55><td class="source">#define PRId8       &quot;d&quot;<br></td></tr
><tr
id=sl_svn55_56><td class="source">#define PRIi8       &quot;i&quot;<br></td></tr
><tr
id=sl_svn55_57><td class="source">#define PRIdLEAST8  &quot;d&quot;<br></td></tr
><tr
id=sl_svn55_58><td class="source">#define PRIiLEAST8  &quot;i&quot;<br></td></tr
><tr
id=sl_svn55_59><td class="source">#define PRIdFAST8   &quot;d&quot;<br></td></tr
><tr
id=sl_svn55_60><td class="source">#define PRIiFAST8   &quot;i&quot;<br></td></tr
><tr
id=sl_svn55_61><td class="source"><br></td></tr
><tr
id=sl_svn55_62><td class="source">#define PRId16       &quot;hd&quot;<br></td></tr
><tr
id=sl_svn55_63><td class="source">#define PRIi16       &quot;hi&quot;<br></td></tr
><tr
id=sl_svn55_64><td class="source">#define PRIdLEAST16  &quot;hd&quot;<br></td></tr
><tr
id=sl_svn55_65><td class="source">#define PRIiLEAST16  &quot;hi&quot;<br></td></tr
><tr
id=sl_svn55_66><td class="source">#define PRIdFAST16   &quot;hd&quot;<br></td></tr
><tr
id=sl_svn55_67><td class="source">#define PRIiFAST16   &quot;hi&quot;<br></td></tr
><tr
id=sl_svn55_68><td class="source"><br></td></tr
><tr
id=sl_svn55_69><td class="source">#define PRId32       &quot;I32d&quot;<br></td></tr
><tr
id=sl_svn55_70><td class="source">#define PRIi32       &quot;I32i&quot;<br></td></tr
><tr
id=sl_svn55_71><td class="source">#define PRIdLEAST32  &quot;I32d&quot;<br></td></tr
><tr
id=sl_svn55_72><td class="source">#define PRIiLEAST32  &quot;I32i&quot;<br></td></tr
><tr
id=sl_svn55_73><td class="source">#define PRIdFAST32   &quot;I32d&quot;<br></td></tr
><tr
id=sl_svn55_74><td class="source">#define PRIiFAST32   &quot;I32i&quot;<br></td></tr
><tr
id=sl_svn55_75><td class="source"><br></td></tr
><tr
id=sl_svn55_76><td class="source">#define PRId64       &quot;I64d&quot;<br></td></tr
><tr
id=sl_svn55_77><td class="source">#define PRIi64       &quot;I64i&quot;<br></td></tr
><tr
id=sl_svn55_78><td class="source">#define PRIdLEAST64  &quot;I64d&quot;<br></td></tr
><tr
id=sl_svn55_79><td class="source">#define PRIiLEAST64  &quot;I64i&quot;<br></td></tr
><tr
id=sl_svn55_80><td class="source">#define PRIdFAST64   &quot;I64d&quot;<br></td></tr
><tr
id=sl_svn55_81><td class="source">#define PRIiFAST64   &quot;I64i&quot;<br></td></tr
><tr
id=sl_svn55_82><td class="source"><br></td></tr
><tr
id=sl_svn55_83><td class="source">#define PRIdMAX     &quot;I64d&quot;<br></td></tr
><tr
id=sl_svn55_84><td class="source">#define PRIiMAX     &quot;I64i&quot;<br></td></tr
><tr
id=sl_svn55_85><td class="source"><br></td></tr
><tr
id=sl_svn55_86><td class="source">#define PRIdPTR     &quot;Id&quot;<br></td></tr
><tr
id=sl_svn55_87><td class="source">#define PRIiPTR     &quot;Ii&quot;<br></td></tr
><tr
id=sl_svn55_88><td class="source"><br></td></tr
><tr
id=sl_svn55_89><td class="source">// The fprintf macros for unsigned integers are:<br></td></tr
><tr
id=sl_svn55_90><td class="source">#define PRIo8       &quot;o&quot;<br></td></tr
><tr
id=sl_svn55_91><td class="source">#define PRIu8       &quot;u&quot;<br></td></tr
><tr
id=sl_svn55_92><td class="source">#define PRIx8       &quot;x&quot;<br></td></tr
><tr
id=sl_svn55_93><td class="source">#define PRIX8       &quot;X&quot;<br></td></tr
><tr
id=sl_svn55_94><td class="source">#define PRIoLEAST8  &quot;o&quot;<br></td></tr
><tr
id=sl_svn55_95><td class="source">#define PRIuLEAST8  &quot;u&quot;<br></td></tr
><tr
id=sl_svn55_96><td class="source">#define PRIxLEAST8  &quot;x&quot;<br></td></tr
><tr
id=sl_svn55_97><td class="source">#define PRIXLEAST8  &quot;X&quot;<br></td></tr
><tr
id=sl_svn55_98><td class="source">#define PRIoFAST8   &quot;o&quot;<br></td></tr
><tr
id=sl_svn55_99><td class="source">#define PRIuFAST8   &quot;u&quot;<br></td></tr
><tr
id=sl_svn55_100><td class="source">#define PRIxFAST8   &quot;x&quot;<br></td></tr
><tr
id=sl_svn55_101><td class="source">#define PRIXFAST8   &quot;X&quot;<br></td></tr
><tr
id=sl_svn55_102><td class="source"><br></td></tr
><tr
id=sl_svn55_103><td class="source">#define PRIo16       &quot;ho&quot;<br></td></tr
><tr
id=sl_svn55_104><td class="source">#define PRIu16       &quot;hu&quot;<br></td></tr
><tr
id=sl_svn55_105><td class="source">#define PRIx16       &quot;hx&quot;<br></td></tr
><tr
id=sl_svn55_106><td class="source">#define PRIX16       &quot;hX&quot;<br></td></tr
><tr
id=sl_svn55_107><td class="source">#define PRIoLEAST16  &quot;ho&quot;<br></td></tr
><tr
id=sl_svn55_108><td class="source">#define PRIuLEAST16  &quot;hu&quot;<br></td></tr
><tr
id=sl_svn55_109><td class="source">#define PRIxLEAST16  &quot;hx&quot;<br></td></tr
><tr
id=sl_svn55_110><td class="source">#define PRIXLEAST16  &quot;hX&quot;<br></td></tr
><tr
id=sl_svn55_111><td class="source">#define PRIoFAST16   &quot;ho&quot;<br></td></tr
><tr
id=sl_svn55_112><td class="source">#define PRIuFAST16   &quot;hu&quot;<br></td></tr
><tr
id=sl_svn55_113><td class="source">#define PRIxFAST16   &quot;hx&quot;<br></td></tr
><tr
id=sl_svn55_114><td class="source">#define PRIXFAST16   &quot;hX&quot;<br></td></tr
><tr
id=sl_svn55_115><td class="source"><br></td></tr
><tr
id=sl_svn55_116><td class="source">#define PRIo32       &quot;I32o&quot;<br></td></tr
><tr
id=sl_svn55_117><td class="source">#define PRIu32       &quot;I32u&quot;<br></td></tr
><tr
id=sl_svn55_118><td class="source">#define PRIx32       &quot;I32x&quot;<br></td></tr
><tr
id=sl_svn55_119><td class="source">#define PRIX32       &quot;I32X&quot;<br></td></tr
><tr
id=sl_svn55_120><td class="source">#define PRIoLEAST32  &quot;I32o&quot;<br></td></tr
><tr
id=sl_svn55_121><td class="source">#define PRIuLEAST32  &quot;I32u&quot;<br></td></tr
><tr
id=sl_svn55_122><td class="source">#define PRIxLEAST32  &quot;I32x&quot;<br></td></tr
><tr
id=sl_svn55_123><td class="source">#define PRIXLEAST32  &quot;I32X&quot;<br></td></tr
><tr
id=sl_svn55_124><td class="source">#define PRIoFAST32   &quot;I32o&quot;<br></td></tr
><tr
id=sl_svn55_125><td class="source">#define PRIuFAST32   &quot;I32u&quot;<br></td></tr
><tr
id=sl_svn55_126><td class="source">#define PRIxFAST32   &quot;I32x&quot;<br></td></tr
><tr
id=sl_svn55_127><td class="source">#define PRIXFAST32   &quot;I32X&quot;<br></td></tr
><tr
id=sl_svn55_128><td class="source"><br></td></tr
><tr
id=sl_svn55_129><td class="source">#define PRIo64       &quot;I64o&quot;<br></td></tr
><tr
id=sl_svn55_130><td class="source">#define PRIu64       &quot;I64u&quot;<br></td></tr
><tr
id=sl_svn55_131><td class="source">#define PRIx64       &quot;I64x&quot;<br></td></tr
><tr
id=sl_svn55_132><td class="source">#define PRIX64       &quot;I64X&quot;<br></td></tr
><tr
id=sl_svn55_133><td class="source">#define PRIoLEAST64  &quot;I64o&quot;<br></td></tr
><tr
id=sl_svn55_134><td class="source">#define PRIuLEAST64  &quot;I64u&quot;<br></td></tr
><tr
id=sl_svn55_135><td class="source">#define PRIxLEAST64  &quot;I64x&quot;<br></td></tr
><tr
id=sl_svn55_136><td class="source">#define PRIXLEAST64  &quot;I64X&quot;<br></td></tr
><tr
id=sl_svn55_137><td class="source">#define PRIoFAST64   &quot;I64o&quot;<br></td></tr
><tr
id=sl_svn55_138><td class="source">#define PRIuFAST64   &quot;I64u&quot;<br></td></tr
><tr
id=sl_svn55_139><td class="source">#define PRIxFAST64   &quot;I64x&quot;<br></td></tr
><tr
id=sl_svn55_140><td class="source">#define PRIXFAST64   &quot;I64X&quot;<br></td></tr
><tr
id=sl_svn55_141><td class="source"><br></td></tr
><tr
id=sl_svn55_142><td class="source">#define PRIoMAX     &quot;I64o&quot;<br></td></tr
><tr
id=sl_svn55_143><td class="source">#define PRIuMAX     &quot;I64u&quot;<br></td></tr
><tr
id=sl_svn55_144><td class="source">#define PRIxMAX     &quot;I64x&quot;<br></td></tr
><tr
id=sl_svn55_145><td class="source">#define PRIXMAX     &quot;I64X&quot;<br></td></tr
><tr
id=sl_svn55_146><td class="source"><br></td></tr
><tr
id=sl_svn55_147><td class="source">#define PRIoPTR     &quot;Io&quot;<br></td></tr
><tr
id=sl_svn55_148><td class="source">#define PRIuPTR     &quot;Iu&quot;<br></td></tr
><tr
id=sl_svn55_149><td class="source">#define PRIxPTR     &quot;Ix&quot;<br></td></tr
><tr
id=sl_svn55_150><td class="source">#define PRIXPTR     &quot;IX&quot;<br></td></tr
><tr
id=sl_svn55_151><td class="source"><br></td></tr
><tr
id=sl_svn55_152><td class="source">// The fscanf macros for signed integers are:<br></td></tr
><tr
id=sl_svn55_153><td class="source">#define SCNd8       &quot;d&quot;<br></td></tr
><tr
id=sl_svn55_154><td class="source">#define SCNi8       &quot;i&quot;<br></td></tr
><tr
id=sl_svn55_155><td class="source">#define SCNdLEAST8  &quot;d&quot;<br></td></tr
><tr
id=sl_svn55_156><td class="source">#define SCNiLEAST8  &quot;i&quot;<br></td></tr
><tr
id=sl_svn55_157><td class="source">#define SCNdFAST8   &quot;d&quot;<br></td></tr
><tr
id=sl_svn55_158><td class="source">#define SCNiFAST8   &quot;i&quot;<br></td></tr
><tr
id=sl_svn55_159><td class="source"><br></td></tr
><tr
id=sl_svn55_160><td class="source">#define SCNd16       &quot;hd&quot;<br></td></tr
><tr
id=sl_svn55_161><td class="source">#define SCNi16       &quot;hi&quot;<br></td></tr
><tr
id=sl_svn55_162><td class="source">#define SCNdLEAST16  &quot;hd&quot;<br></td></tr
><tr
id=sl_svn55_163><td class="source">#define SCNiLEAST16  &quot;hi&quot;<br></td></tr
><tr
id=sl_svn55_164><td class="source">#define SCNdFAST16   &quot;hd&quot;<br></td></tr
><tr
id=sl_svn55_165><td class="source">#define SCNiFAST16   &quot;hi&quot;<br></td></tr
><tr
id=sl_svn55_166><td class="source"><br></td></tr
><tr
id=sl_svn55_167><td class="source">#define SCNd32       &quot;ld&quot;<br></td></tr
><tr
id=sl_svn55_168><td class="source">#define SCNi32       &quot;li&quot;<br></td></tr
><tr
id=sl_svn55_169><td class="source">#define SCNdLEAST32  &quot;ld&quot;<br></td></tr
><tr
id=sl_svn55_170><td class="source">#define SCNiLEAST32  &quot;li&quot;<br></td></tr
><tr
id=sl_svn55_171><td class="source">#define SCNdFAST32   &quot;ld&quot;<br></td></tr
><tr
id=sl_svn55_172><td class="source">#define SCNiFAST32   &quot;li&quot;<br></td></tr
><tr
id=sl_svn55_173><td class="source"><br></td></tr
><tr
id=sl_svn55_174><td class="source">#define SCNd64       &quot;I64d&quot;<br></td></tr
><tr
id=sl_svn55_175><td class="source">#define SCNi64       &quot;I64i&quot;<br></td></tr
><tr
id=sl_svn55_176><td class="source">#define SCNdLEAST64  &quot;I64d&quot;<br></td></tr
><tr
id=sl_svn55_177><td class="source">#define SCNiLEAST64  &quot;I64i&quot;<br></td></tr
><tr
id=sl_svn55_178><td class="source">#define SCNdFAST64   &quot;I64d&quot;<br></td></tr
><tr
id=sl_svn55_179><td class="source">#define SCNiFAST64   &quot;I64i&quot;<br></td></tr
><tr
id=sl_svn55_180><td class="source"><br></td></tr
><tr
id=sl_svn55_181><td class="source">#define SCNdMAX     &quot;I64d&quot;<br></td></tr
><tr
id=sl_svn55_182><td class="source">#define SCNiMAX     &quot;I64i&quot;<br></td></tr
><tr
id=sl_svn55_183><td class="source"><br></td></tr
><tr
id=sl_svn55_184><td class="source">#ifdef _WIN64 // [<br></td></tr
><tr
id=sl_svn55_185><td class="source">#  define SCNdPTR     &quot;I64d&quot;<br></td></tr
><tr
id=sl_svn55_186><td class="source">#  define SCNiPTR     &quot;I64i&quot;<br></td></tr
><tr
id=sl_svn55_187><td class="source">#else  // _WIN64 ][<br></td></tr
><tr
id=sl_svn55_188><td class="source">#  define SCNdPTR     &quot;ld&quot;<br></td></tr
><tr
id=sl_svn55_189><td class="source">#  define SCNiPTR     &quot;li&quot;<br></td></tr
><tr
id=sl_svn55_190><td class="source">#endif  // _WIN64 ]<br></td></tr
><tr
id=sl_svn55_191><td class="source"><br></td></tr
><tr
id=sl_svn55_192><td class="source">// The fscanf macros for unsigned integers are:<br></td></tr
><tr
id=sl_svn55_193><td class="source">#define SCNo8       &quot;o&quot;<br></td></tr
><tr
id=sl_svn55_194><td class="source">#define SCNu8       &quot;u&quot;<br></td></tr
><tr
id=sl_svn55_195><td class="source">#define SCNx8       &quot;x&quot;<br></td></tr
><tr
id=sl_svn55_196><td class="source">#define SCNX8       &quot;X&quot;<br></td></tr
><tr
id=sl_svn55_197><td class="source">#define SCNoLEAST8  &quot;o&quot;<br></td></tr
><tr
id=sl_svn55_198><td class="source">#define SCNuLEAST8  &quot;u&quot;<br></td></tr
><tr
id=sl_svn55_199><td class="source">#define SCNxLEAST8  &quot;x&quot;<br></td></tr
><tr
id=sl_svn55_200><td class="source">#define SCNXLEAST8  &quot;X&quot;<br></td></tr
><tr
id=sl_svn55_201><td class="source">#define SCNoFAST8   &quot;o&quot;<br></td></tr
><tr
id=sl_svn55_202><td class="source">#define SCNuFAST8   &quot;u&quot;<br></td></tr
><tr
id=sl_svn55_203><td class="source">#define SCNxFAST8   &quot;x&quot;<br></td></tr
><tr
id=sl_svn55_204><td class="source">#define SCNXFAST8   &quot;X&quot;<br></td></tr
></table></pre>

<pre class="prettyprint "><table><tr
id=sl_svn55_205><td class="source"><br></td></tr
><tr
id=sl_svn55_206><td class="source">#define SCNo16       &quot;ho&quot;<br></td></tr
><tr
id=sl_svn55_207><td class="source">#define SCNu16       &quot;hu&quot;<br></td></tr
><tr
id=sl_svn55_208><td class="source">#define SCNx16       &quot;hx&quot;<br></td></tr
><tr
id=sl_svn55_209><td class="source">#define SCNX16       &quot;hX&quot;<br></td></tr
><tr
id=sl_svn55_210><td class="source">#define SCNoLEAST16  &quot;ho&quot;<br></td></tr
><tr
id=sl_svn55_211><td class="source">#define SCNuLEAST16  &quot;hu&quot;<br></td></tr
><tr
id=sl_svn55_212><td class="source">#define SCNxLEAST16  &quot;hx&quot;<br></td></tr
><tr
id=sl_svn55_213><td class="source">#define SCNXLEAST16  &quot;hX&quot;<br></td></tr
><tr
id=sl_svn55_214><td class="source">#define SCNoFAST16   &quot;ho&quot;<br></td></tr
><tr
id=sl_svn55_215><td class="source">#define SCNuFAST16   &quot;hu&quot;<br></td></tr
><tr
id=sl_svn55_216><td class="source">#define SCNxFAST16   &quot;hx&quot;<br></td></tr
><tr
id=sl_svn55_217><td class="source">#define SCNXFAST16   &quot;hX&quot;<br></td></tr
><tr
id=sl_svn55_218><td class="source"><br></td></tr
><tr
id=sl_svn55_219><td class="source">#define SCNo32       &quot;lo&quot;<br></td></tr
><tr
id=sl_svn55_220><td class="source">#define SCNu32       &quot;lu&quot;<br></td></tr
><tr
id=sl_svn55_221><td class="source">#define SCNx32       &quot;lx&quot;<br></td></tr
><tr
id=sl_svn55_222><td class="source">#define SCNX32       &quot;lX&quot;<br></td></tr
><tr
id=sl_svn55_223><td class="source">#define SCNoLEAST32  &quot;lo&quot;<br></td></tr
><tr
id=sl_svn55_224><td class="source">#define SCNuLEAST32  &quot;lu&quot;<br></td></tr
><tr
id=sl_svn55_225><td class="source">#define SCNxLEAST32  &quot;lx&quot;<br></td></tr
><tr
id=sl_svn55_226><td class="source">#define SCNXLEAST32  &quot;lX&quot;<br></td></tr
><tr
id=sl_svn55_227><td class="source">#define SCNoFAST32   &quot;lo&quot;<br></td></tr
><tr
id=sl_svn55_228><td class="source">#define SCNuFAST32   &quot;lu&quot;<br></td></tr
><tr
id=sl_svn55_229><td class="source">#define SCNxFAST32   &quot;lx&quot;<br></td></tr
><tr
id=sl_svn55_230><td class="source">#define SCNXFAST32   &quot;lX&quot;<br></td></tr
><tr
id=sl_svn55_231><td class="source"><br></td></tr
><tr
id=sl_svn55_232><td class="source">#define SCNo64       &quot;I64o&quot;<br></td></tr
><tr
id=sl_svn55_233><td class="source">#define SCNu64       &quot;I64u&quot;<br></td></tr
><tr
id=sl_svn55_234><td class="source">#define SCNx64       &quot;I64x&quot;<br></td></tr
><tr
id=sl_svn55_235><td class="source">#define SCNX64       &quot;I64X&quot;<br></td></tr
><tr
id=sl_svn55_236><td class="source">#define SCNoLEAST64  &quot;I64o&quot;<br></td></tr
><tr
id=sl_svn55_237><td class="source">#define SCNuLEAST64  &quot;I64u&quot;<br></td></tr
><tr
id=sl_svn55_238><td class="source">#define SCNxLEAST64  &quot;I64x&quot;<br></td></tr
><tr
id=sl_svn55_239><td class="source">#define SCNXLEAST64  &quot;I64X&quot;<br></td></tr
><tr
id=sl_svn55_240><td class="source">#define SCNoFAST64   &quot;I64o&quot;<br></td></tr
><tr
id=sl_svn55_241><td class="source">#define SCNuFAST64   &quot;I64u&quot;<br></td></tr
><tr
id=sl_svn55_242><td class="source">#define SCNxFAST64   &quot;I64x&quot;<br></td></tr
><tr
id=sl_svn55_243><td class="source">#define SCNXFAST64   &quot;I64X&quot;<br></td></tr
><tr
id=sl_svn55_244><td class="source"><br></td></tr
><tr
id=sl_svn55_245><td class="source">#define SCNoMAX     &quot;I64o&quot;<br></td></tr
><tr
id=sl_svn55_246><td class="source">#define SCNuMAX     &quot;I64u&quot;<br></td></tr
><tr
id=sl_svn55_247><td class="source">#define SCNxMAX     &quot;I64x&quot;<br></td></tr
><tr
id=sl_svn55_248><td class="source">#define SCNXMAX     &quot;I64X&quot;<br></td></tr
><tr
id=sl_svn55_249><td class="source"><br></td></tr
><tr
id=sl_svn55_250><td class="source">#ifdef _WIN64 // [<br></td></tr
><tr
id=sl_svn55_251><td class="source">#  define SCNoPTR     &quot;I64o&quot;<br></td></tr
><tr
id=sl_svn55_252><td class="source">#  define SCNuPTR     &quot;I64u&quot;<br></td></tr
><tr
id=sl_svn55_253><td class="source">#  define SCNxPTR     &quot;I64x&quot;<br></td></tr
><tr
id=sl_svn55_254><td class="source">#  define SCNXPTR     &quot;I64X&quot;<br></td></tr
><tr
id=sl_svn55_255><td class="source">#else  // _WIN64 ][<br></td></tr
><tr
id=sl_svn55_256><td class="source">#  define SCNoPTR     &quot;lo&quot;<br></td></tr
><tr
id=sl_svn55_257><td class="source">#  define SCNuPTR     &quot;lu&quot;<br></td></tr
><tr
id=sl_svn55_258><td class="source">#  define SCNxPTR     &quot;lx&quot;<br></td></tr
><tr
id=sl_svn55_259><td class="source">#  define SCNXPTR     &quot;lX&quot;<br></td></tr
><tr
id=sl_svn55_260><td class="source">#endif  // _WIN64 ]<br></td></tr
><tr
id=sl_svn55_261><td class="source"><br></td></tr
><tr
id=sl_svn55_262><td class="source">// 7.8.2 Functions for greatest-width integer types<br></td></tr
><tr
id=sl_svn55_263><td class="source"><br></td></tr
><tr
id=sl_svn55_264><td class="source">// 7.8.2.1 The imaxabs function<br></td></tr
><tr
id=sl_svn55_265><td class="source">#define imaxabs _abs64<br></td></tr
><tr
id=sl_svn55_266><td class="source"><br></td></tr
><tr
id=sl_svn55_267><td class="source">// 7.8.2.2 The imaxdiv function<br></td></tr
><tr
id=sl_svn55_268><td class="source"><br></td></tr
><tr
id=sl_svn55_269><td class="source">// This is modified version of div() function from Microsoft&#39;s div.c found<br></td></tr
><tr
id=sl_svn55_270><td class="source">// in %MSVC.NET%\crt\src\div.c<br></td></tr
><tr
id=sl_svn55_271><td class="source">#ifdef STATIC_IMAXDIV // [<br></td></tr
><tr
id=sl_svn55_272><td class="source">static<br></td></tr
><tr
id=sl_svn55_273><td class="source">#else // STATIC_IMAXDIV ][<br></td></tr
><tr
id=sl_svn55_274><td class="source">_inline<br></td></tr
><tr
id=sl_svn55_275><td class="source">#endif // STATIC_IMAXDIV ]<br></td></tr
><tr
id=sl_svn55_276><td class="source">imaxdiv_t __cdecl imaxdiv(intmax_t numer, intmax_t denom)<br></td></tr
><tr
id=sl_svn55_277><td class="source">{<br></td></tr
><tr
id=sl_svn55_278><td class="source">   imaxdiv_t result;<br></td></tr
><tr
id=sl_svn55_279><td class="source"><br></td></tr
><tr
id=sl_svn55_280><td class="source">   result.quot = numer / denom;<br></td></tr
><tr
id=sl_svn55_281><td class="source">   result.rem = numer % denom;<br></td></tr
><tr
id=sl_svn55_282><td class="source"><br></td></tr
><tr
id=sl_svn55_283><td class="source">   if (numer &lt; 0 &amp;&amp; result.rem &gt; 0) {<br></td></tr
><tr
id=sl_svn55_284><td class="source">      // did division wrong; must fix up<br></td></tr
><tr
id=sl_svn55_285><td class="source">      ++result.quot;<br></td></tr
><tr
id=sl_svn55_286><td class="source">      result.rem -= denom;<br></td></tr
><tr
id=sl_svn55_287><td class="source">   }<br></td></tr
><tr
id=sl_svn55_288><td class="source"><br></td></tr
><tr
id=sl_svn55_289><td class="source">   return result;<br></td></tr
><tr
id=sl_svn55_290><td class="source">}<br></td></tr
><tr
id=sl_svn55_291><td class="source"><br></td></tr
><tr
id=sl_svn55_292><td class="source">// 7.8.2.3 The strtoimax and strtoumax functions<br></td></tr
><tr
id=sl_svn55_293><td class="source">#define strtoimax _strtoi64<br></td></tr
><tr
id=sl_svn55_294><td class="source">#define strtoumax _strtoui64<br></td></tr
><tr
id=sl_svn55_295><td class="source"><br></td></tr
><tr
id=sl_svn55_296><td class="source">// 7.8.2.4 The wcstoimax and wcstoumax functions<br></td></tr
><tr
id=sl_svn55_297><td class="source">#define wcstoimax _wcstoi64<br></td></tr
><tr
id=sl_svn55_298><td class="source">#define wcstoumax _wcstoui64<br></td></tr
><tr
id=sl_svn55_299><td class="source"><br></td></tr
><tr
id=sl_svn55_300><td class="source"><br></td></tr
><tr
id=sl_svn55_301><td class="source">#endif // _MSC_INTTYPES_H_ ]<br></td></tr
></table></pre>

<pre class="prettyprint"><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
</td>
</tr></table>



 <div id="log">
 <div style="text-align:right">
 <a class="ifCollapse" href="#" onclick="_toggleMeta('', 'p', 'baseutils', this)">Show details</a>
 <a class="ifExpand" href="#" onclick="_toggleMeta('', 'p', 'baseutils', this)">Hide details</a>
 </div>
 <div class="ifExpand">
 
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="changelog">
 <p>Change log</p>
 <div>
 <a href="/p/baseutils/source/detail?spec=svn106&r=55">r55</a>
 by kkowalczyk
 on Jul 30, 2007
 &nbsp; <a href="/p/baseutils/source/diff?spec=svn106&r=55&amp;format=side&amp;path=/trunk/msvc/inttypes.h&amp;old_path=/trunk/msvc/inttypes.h&amp;old=">Diff</a>
 </div>
 <pre>adding stdint.h and inttypes.h C99
emulation for Visual Studio</pre>
 </div>
 
 
 
 
 
 
 <script type="text/javascript">
 var detail_url = '/p/baseutils/source/detail?r=55&spec=svn106';
 var publish_url = '/p/baseutils/source/detail?r=55&spec=svn106#publish';
 // describe the paths of this revision in javascript.
 var changed_paths = [];
 var changed_urls = [];
 
 changed_paths.push('/trunk/msvc');
 changed_urls.push('/p/baseutils/source/browse/trunk/msvc?r=55&spec=svn106');
 
 
 changed_paths.push('/trunk/msvc/inttypes.h');
 changed_urls.push('/p/baseutils/source/browse/trunk/msvc/inttypes.h?r=55&spec=svn106');
 
 var selected_path = '/trunk/msvc/inttypes.h';
 
 
 changed_paths.push('/trunk/msvc/stdint.h');
 changed_urls.push('/p/baseutils/source/browse/trunk/msvc/stdint.h?r=55&spec=svn106');
 
 
 changed_paths.push('/trunk/pstdint.h');
 changed_urls.push('/p/baseutils/source/browse/trunk/pstdint.h?r=55&spec=svn106');
 
 
 function getCurrentPageIndex() {
 for (var i = 0; i < changed_paths.length; i++) {
 if (selected_path == changed_paths[i]) {
 return i;
 }
 }
 }
 function getNextPage() {
 var i = getCurrentPageIndex();
 if (i < changed_paths.length - 1) {
 return changed_urls[i + 1];
 }
 return null;
 }
 function getPreviousPage() {
 var i = getCurrentPageIndex();
 if (i > 0) {
 return changed_urls[i - 1];
 }
 return null;
 }
 function gotoNextPage() {
 var page = getNextPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoPreviousPage() {
 var page = getPreviousPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoDetailPage() {
 window.location = detail_url;
 }
 function gotoPublishPage() {
 window.location = publish_url;
 }
</script>
 
 <style type="text/css">
 #review_nav {
 border-top: 3px solid white;
 padding-top: 6px;
 margin-top: 1em;
 }
 #review_nav td {
 vertical-align: middle;
 }
 #review_nav select {
 margin: .5em 0;
 }
 </style>
 <div id="review_nav">
 <table><tr><td>Go to:&nbsp;</td><td>
 <select name="files_in_rev" onchange="window.location=this.value">
 
 <option value="/p/baseutils/source/browse/trunk/msvc?r=55&amp;spec=svn106"
 
 >/trunk/msvc</option>
 
 <option value="/p/baseutils/source/browse/trunk/msvc/inttypes.h?r=55&amp;spec=svn106"
 selected="selected"
 >/trunk/msvc/inttypes.h</option>
 
 <option value="/p/baseutils/source/browse/trunk/msvc/stdint.h?r=55&amp;spec=svn106"
 
 >/trunk/msvc/stdint.h</option>
 
 <option value="/p/baseutils/source/browse/trunk/pstdint.h?r=55&amp;spec=svn106"
 
 >/trunk/pstdint.h</option>
 
 </select>
 </td></tr></table>
 
 
 




 <div style="white-space:nowrap">
 Project members,
 <a href="https://www.google.com/accounts/ServiceLogin?service=code&amp;ltmpl=phosting&amp;continue=http%3A%2F%2Fcode.google.com%2Fp%2Fbaseutils%2Fsource%2Fbrowse%2Ftrunk%2Fmsvc%2Finttypes.h&amp;followup=http%3A%2F%2Fcode.google.com%2Fp%2Fbaseutils%2Fsource%2Fbrowse%2Ftrunk%2Fmsvc%2Finttypes.h"
 >sign in</a> to write a code review</div>


 
 </div>
 
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="older_bubble">
 <p>Older revisions</p>
 
 <a href="/p/baseutils/source/list?path=/trunk/msvc/inttypes.h&start=55">All revisions of this file</a>
 </div>
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="fileinfo_bubble">
 <p>File info</p>
 
 <div>Size: 7874 bytes,
 301 lines</div>
 
 <div><a href="http://baseutils.googlecode.com/svn/trunk/msvc/inttypes.h">View raw file</a></div>
 </div>
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 </div>
 </div>


</div>
</div>

 <script src="http://www.gstatic.com/codesite/ph/11982002900633812604/js/prettify/prettify.js"></script>

<script type="text/javascript">prettyPrint();</script>

<script src="http://www.gstatic.com/codesite/ph/11982002900633812604/js/source_file_scripts.js"></script>

 <script type="text/javascript" src="http://kibbles.googlecode.com/files/kibbles-1.3.1.comp.js"></script>
 <script type="text/javascript">
 var lastStop = null;
 var initilized = false;
 
 function updateCursor(next, prev) {
 if (prev && prev.element) {
 prev.element.className = 'cursor_stop cursor_hidden';
 }
 if (next && next.element) {
 next.element.className = 'cursor_stop cursor';
 lastStop = next.index;
 }
 }
 
 function pubRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initilized) {
 reloadCursors();
 }
 }
 
 function draftRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initilized) {
 reloadCursors();
 }
 }
 
 function draftDestroyed(data) {
 updateCursorForCell(data.cellId, 'nocursor');
 if (initilized) {
 reloadCursors();
 }
 }
 function reloadCursors() {
 kibbles.skipper.reset();
 loadCursors();
 if (lastStop != null) {
 kibbles.skipper.setCurrentStop(lastStop);
 }
 }
 // possibly the simplest way to insert any newly added comments
 // is to update the class of the corresponding cursor row,
 // then refresh the entire list of rows.
 function updateCursorForCell(cellId, className) {
 var cell = document.getElementById(cellId);
 // we have to go two rows back to find the cursor location
 var row = getPreviousElement(cell.parentNode);
 row.className = className;
 }
 // returns the previous element, ignores text nodes.
 function getPreviousElement(e) {
 var element = e.previousSibling;
 if (element.nodeType == 3) {
 element = element.previousSibling;
 }
 if (element && element.tagName) {
 return element;
 }
 }
 function loadCursors() {
 // register our elements with skipper
 var elements = CR_getElements('*', 'cursor_stop');
 var len = elements.length;
 for (var i = 0; i < len; i++) {
 var element = elements[i]; 
 element.className = 'cursor_stop cursor_hidden';
 kibbles.skipper.append(element);
 }
 }
 function toggleComments() {
 CR_toggleCommentDisplay();
 reloadCursors();
 }
 function keysOnLoadHandler() {
 // setup skipper
 kibbles.skipper.addStopListener(
 kibbles.skipper.LISTENER_TYPE.PRE, updateCursor);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_top', 50);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_bottom', 100);
 // Register our keys
 kibbles.skipper.addFwdKey("n");
 kibbles.skipper.addRevKey("p");
 kibbles.keys.addKeyPressListener(
 'u', function() { window.location = detail_url; });
 kibbles.keys.addKeyPressListener(
 'r', function() { window.location = detail_url + '#publish'; });
 
 kibbles.keys.addKeyPressListener('j', gotoNextPage);
 kibbles.keys.addKeyPressListener('k', gotoPreviousPage);
 
 
 }
 window.onload = function() {keysOnLoadHandler();};
 </script>


<!-- code review support -->
<script src="http://www.gstatic.com/codesite/ph/11982002900633812604/js/code_review_scripts.js"></script>
<script type="text/javascript">
 
 // the comment form template
 var form = '<div class="draft"><div class="header"><span class="title">Draft comment:</span></div>' +
 '<div class="body"><form onsubmit="return false;"><textarea id="$ID">$BODY</textarea><br>$ACTIONS</form></div>' +
 '</div>';
 // the comment "plate" template used for both draft and published comment "plates".
 var draft_comment = '<div class="draft" ondblclick="$ONDBLCLICK">' +
 '<div class="header"><span class="title">Draft comment:</span><span class="actions">$ACTIONS</span></div>' +
 '<pre id="$ID" class="body">$BODY</pre>' +
 '</div>';
 var published_comment = '<div class="published">' +
 '<div class="header"><span class="title"><a href="$PROFILE_URL">$AUTHOR:</a></span><div>' +
 '<pre id="$ID" class="body">$BODY</pre>' +
 '</div>';

 function showPublishInstructions() {
 var element = document.getElementById('review_instr');
 if (element) {
 element.className = 'opened';
 }
 }
 function revsOnLoadHandler() {
 // register our source container with the commenting code
 var paths = {'svn55': '/trunk/msvc/inttypes.h'}
 CR_setup('', 'p', 'baseutils', '', 'svn106', paths,
 '', CR_BrowseIntegrationFactory);
 // register our hidden ui elements with the code commenting code ui builder.
 CR_registerLayoutElement('form', form);
 CR_registerLayoutElement('draft_comment', draft_comment);
 CR_registerLayoutElement('published_comment', published_comment);
 
 CR_registerActivityListener(CR_ACTIVITY_TYPE.REVEAL_DRAFT_PLATE, showPublishInstructions);
 
 CR_registerActivityListener(CR_ACTIVITY_TYPE.REVEAL_PUB_PLATE, pubRevealed);
 CR_registerActivityListener(CR_ACTIVITY_TYPE.REVEAL_DRAFT_PLATE, draftRevealed);
 CR_registerActivityListener(CR_ACTIVITY_TYPE.DISCARD_DRAFT_COMMENT, draftDestroyed);
 
 
 
 
 
 
 
 
 
 var initilized = true;
 reloadCursors();
 }
 window.onload = function() {keysOnLoadHandler(); revsOnLoadHandler();};
</script>

<script type="text/javascript" src="http://www.gstatic.com/codesite/ph/11982002900633812604/js/dit_scripts_20081013.js"></script>

 
 
 <script type="text/javascript" src="http://www.gstatic.com/codesite/ph/11982002900633812604/js/core_scripts_20081103.js"></script>
 <script type="text/javascript" src="/js/codesite_product_dictionary_ph.pack.04102009.js"></script>
 </div>
<div id="footer" dir="ltr">
 
 <div class="text">
 
 &copy;2010 Google -
 <a href="/projecthosting/terms.html">Terms</a> -
 <a href="http://www.google.com/privacy.html">Privacy</a> -
 <a href="/p/support/">Project Hosting Help</a>
 
 </div>
</div>

 <div class="hostedBy" style="margin-top: -20px;">
 <span style="vertical-align: top;">Powered by <a href="http://code.google.com/projecthosting/">Google Project Hosting</a></span>
 </div>
 
 


 
 </body>
</html>

