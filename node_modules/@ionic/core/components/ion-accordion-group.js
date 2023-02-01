/*!
 * (C) Ionic http://ionicframework.com - MIT License
 */
import { proxyCustomElement, HTMLElement, createEvent, h, Host } from '@stencil/core/internal/client';
import { b as getIonMode } from './ionic-global.js';

const accordionGroupIosCss = ":host{display:block}:host(.accordion-group-expand-inset){margin-left:16px;margin-right:16px;margin-top:16px;margin-bottom:16px}@supports ((-webkit-margin-start: 0) or (margin-inline-start: 0)) or (-webkit-margin-start: 0){:host(.accordion-group-expand-inset){margin-left:unset;margin-right:unset;-webkit-margin-start:16px;margin-inline-start:16px;-webkit-margin-end:16px;margin-inline-end:16px}}:host(.accordion-group-expand-inset) ::slotted(ion-accordion.accordion-expanding),:host(.accordion-group-expand-inset) ::slotted(ion-accordion.accordion-expanded){border-bottom:none}";

const accordionGroupMdCss = ":host{display:block}:host(.accordion-group-expand-inset){margin-left:16px;margin-right:16px;margin-top:16px;margin-bottom:16px}@supports ((-webkit-margin-start: 0) or (margin-inline-start: 0)) or (-webkit-margin-start: 0){:host(.accordion-group-expand-inset){margin-left:unset;margin-right:unset;-webkit-margin-start:16px;margin-inline-start:16px;-webkit-margin-end:16px;margin-inline-end:16px}}:host(.accordion-group-expand-inset) ::slotted(ion-accordion){-webkit-box-shadow:0px 3px 1px -2px rgba(0, 0, 0, 0.2), 0px 2px 2px 0px rgba(0, 0, 0, 0.14), 0px 1px 5px 0px rgba(0, 0, 0, 0.12);box-shadow:0px 3px 1px -2px rgba(0, 0, 0, 0.2), 0px 2px 2px 0px rgba(0, 0, 0, 0.14), 0px 1px 5px 0px rgba(0, 0, 0, 0.12)}:host(.accordion-group-expand-inset) ::slotted(ion-accordion.accordion-expanding),:host(.accordion-group-expand-inset) ::slotted(ion-accordion.accordion-expanded){margin-left:0;margin-right:0;margin-top:16px;margin-bottom:16px;border-radius:6px}:host(.accordion-group-expand-inset) ::slotted(ion-accordion.accordion-previous){border-bottom-right-radius:6px;border-bottom-left-radius:6px}:host-context([dir=rtl]):host(.accordion-group-expand-inset) ::slotted(ion-accordion.accordion-previous),:host-context([dir=rtl]).accordion-group-expand-inset ::slotted(ion-accordion.accordion-previous){border-bottom-right-radius:6px;border-bottom-left-radius:6px}:host(.accordion-group-expand-inset) ::slotted(ion-accordion.accordion-next){border-top-left-radius:6px;border-top-right-radius:6px}:host-context([dir=rtl]):host(.accordion-group-expand-inset) ::slotted(ion-accordion.accordion-next),:host-context([dir=rtl]).accordion-group-expand-inset ::slotted(ion-accordion.accordion-next){border-top-left-radius:6px;border-top-right-radius:6px}:host(.accordion-group-expand-inset) ::slotted(ion-accordion):first-of-type{margin-left:0;margin-right:0;margin-top:0;margin-bottom:0}";

const AccordionGroup = /*@__PURE__*/ proxyCustomElement(class extends HTMLElement {
  constructor() {
    super();
    this.__registerHost();
    this.__attachShadow();
    this.ionChange = createEvent(this, "ionChange", 7);
    /**
     * If `true`, all accordions inside of the
     * accordion group will animate when expanding
     * or collapsing.
     */
    this.animated = true;
    /**
     * If `true`, the accordion group cannot be interacted with.
     */
    this.disabled = false;
    /**
     * If `true`, the accordion group cannot be interacted with,
     * but does not alter the opacity.
     */
    this.readonly = false;
    /**
     * Describes the expansion behavior for each accordion.
     * Possible values are `"compact"` and `"inset"`.
     * Defaults to `"compact"`.
     */
    this.expand = 'compact';
  }
  valueChanged() {
    const { value, multiple } = this;
    /**
     * If accordion group does not
     * let multiple accordions be open
     * at once, but user passes an array
     * just grab the first value.
     */
    if (!multiple && Array.isArray(value)) {
      this.value = value[0];
    }
    else {
      this.ionChange.emit({ value: this.value });
    }
  }
  async disabledChanged() {
    const { disabled } = this;
    const accordions = await this.getAccordions();
    for (const accordion of accordions) {
      accordion.disabled = disabled;
    }
  }
  async readonlyChanged() {
    const { readonly } = this;
    const accordions = await this.getAccordions();
    for (const accordion of accordions) {
      accordion.readonly = readonly;
    }
  }
  async onKeydown(ev) {
    const activeElement = document.activeElement;
    if (!activeElement) {
      return;
    }
    /**
     * Make sure focus is in the header, not the body, of the accordion. This ensures
     * that if there are any interactable elements in the body, their keyboard
     * interaction doesn't get stolen by the accordion. Example: using up/down keys
     * in ion-textarea.
     */
    const activeAccordionHeader = activeElement.closest('ion-accordion [slot="header"]');
    if (!activeAccordionHeader) {
      return;
    }
    const accordionEl = activeElement.tagName === 'ION-ACCORDION' ? activeElement : activeElement.closest('ion-accordion');
    if (!accordionEl) {
      return;
    }
    const closestGroup = accordionEl.closest('ion-accordion-group');
    if (closestGroup !== this.el) {
      return;
    }
    // If the active accordion is not in the current array of accordions, do not do anything
    const accordions = await this.getAccordions();
    const startingIndex = accordions.findIndex((a) => a === accordionEl);
    if (startingIndex === -1) {
      return;
    }
    let accordion;
    if (ev.key === 'ArrowDown') {
      accordion = this.findNextAccordion(accordions, startingIndex);
    }
    else if (ev.key === 'ArrowUp') {
      accordion = this.findPreviousAccordion(accordions, startingIndex);
    }
    else if (ev.key === 'Home') {
      accordion = accordions[0];
    }
    else if (ev.key === 'End') {
      accordion = accordions[accordions.length - 1];
    }
    if (accordion !== undefined && accordion !== activeElement) {
      accordion.focus();
    }
  }
  async componentDidLoad() {
    if (this.disabled) {
      this.disabledChanged();
    }
    if (this.readonly) {
      this.readonlyChanged();
    }
  }
  /**
   * @internal
   */
  async requestAccordionToggle(accordionValue, accordionExpand) {
    const { multiple, value, readonly, disabled } = this;
    if (readonly || disabled) {
      return;
    }
    if (accordionExpand) {
      /**
       * If group accepts multiple values
       * check to see if value is already in
       * in values array. If not, add it
       * to the array.
       */
      if (multiple) {
        const groupValue = value !== null && value !== void 0 ? value : [];
        const processedValue = Array.isArray(groupValue) ? groupValue : [groupValue];
        const valueExists = processedValue.find((v) => v === accordionValue);
        if (valueExists === undefined && accordionValue !== undefined) {
          this.value = [...processedValue, accordionValue];
        }
      }
      else {
        this.value = accordionValue;
      }
    }
    else {
      /**
       * If collapsing accordion, either filter the value
       * out of the values array or unset the value.
       */
      if (multiple) {
        const groupValue = value !== null && value !== void 0 ? value : [];
        const processedValue = Array.isArray(groupValue) ? groupValue : [groupValue];
        this.value = processedValue.filter((v) => v !== accordionValue);
      }
      else {
        this.value = undefined;
      }
    }
  }
  findNextAccordion(accordions, startingIndex) {
    const nextAccordion = accordions[startingIndex + 1];
    if (nextAccordion === undefined) {
      return accordions[0];
    }
    return nextAccordion;
  }
  findPreviousAccordion(accordions, startingIndex) {
    const prevAccordion = accordions[startingIndex - 1];
    if (prevAccordion === undefined) {
      return accordions[accordions.length - 1];
    }
    return prevAccordion;
  }
  /**
   * @internal
   */
  async getAccordions() {
    return Array.from(this.el.querySelectorAll(':scope > ion-accordion'));
  }
  render() {
    const { disabled, readonly, expand } = this;
    const mode = getIonMode(this);
    return (h(Host, { class: {
        [mode]: true,
        'accordion-group-disabled': disabled,
        'accordion-group-readonly': readonly,
        [`accordion-group-expand-${expand}`]: true,
      }, role: "presentation" }, h("slot", null)));
  }
  get el() { return this; }
  static get watchers() { return {
    "value": ["valueChanged"],
    "disabled": ["disabledChanged"],
    "readonly": ["readonlyChanged"]
  }; }
  static get style() { return {
    ios: accordionGroupIosCss,
    md: accordionGroupMdCss
  }; }
}, [33, "ion-accordion-group", {
    "animated": [4],
    "multiple": [4],
    "value": [1025],
    "disabled": [4],
    "readonly": [4],
    "expand": [1],
    "requestAccordionToggle": [64],
    "getAccordions": [64]
  }, [[0, "keydown", "onKeydown"]]]);
function defineCustomElement$1() {
  if (typeof customElements === "undefined") {
    return;
  }
  const components = ["ion-accordion-group"];
  components.forEach(tagName => { switch (tagName) {
    case "ion-accordion-group":
      if (!customElements.get(tagName)) {
        customElements.define(tagName, AccordionGroup);
      }
      break;
  } });
}

const IonAccordionGroup = AccordionGroup;
const defineCustomElement = defineCustomElement$1;

export { IonAccordionGroup, defineCustomElement };
