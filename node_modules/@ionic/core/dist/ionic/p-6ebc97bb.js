/*!
 * (C) Ionic http://ionicframework.com - MIT License
 */
import{f as o,c as s}from"./p-d472be56.js";import{f as t,s as r}from"./p-47107f80.js";import{c as e}from"./p-ebe7e343.js";import"./p-d2917828.js";const a=()=>{const a=window;a.addEventListener("statusTap",(()=>{o((()=>{const o=document.elementFromPoint(a.innerWidth/2,a.innerHeight/2);if(!o)return;const n=t(o);n&&new Promise((o=>e(n,o))).then((()=>{s((async()=>{n.style.setProperty("--overflow","hidden"),await r(n,300),n.style.removeProperty("--overflow")}))}))}))}))};export{a as startStatusTap}