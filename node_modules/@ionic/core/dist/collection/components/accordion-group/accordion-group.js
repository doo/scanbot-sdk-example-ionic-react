/*!
 * (C) Ionic http://ionicframework.com - MIT License
 */
import { Host, h } from '@stencil/core';
import { getIonMode } from '../../global/ionic-global';
/**
 * @virtualProp {"ios" | "md"} mode - The mode determines which platform styles to use.
 */
export class AccordionGroup {
  constructor() {
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
  static get is() { return "ion-accordion-group"; }
  static get encapsulation() { return "shadow"; }
  static get originalStyleUrls() {
    return {
      "ios": ["accordion-group.ios.scss"],
      "md": ["accordion-group.md.scss"]
    };
  }
  static get styleUrls() {
    return {
      "ios": ["accordion-group.ios.css"],
      "md": ["accordion-group.md.css"]
    };
  }
  static get properties() {
    return {
      "animated": {
        "type": "boolean",
        "mutable": false,
        "complexType": {
          "original": "boolean",
          "resolved": "boolean",
          "references": {}
        },
        "required": false,
        "optional": false,
        "docs": {
          "tags": [],
          "text": "If `true`, all accordions inside of the\naccordion group will animate when expanding\nor collapsing."
        },
        "attribute": "animated",
        "reflect": false,
        "defaultValue": "true"
      },
      "multiple": {
        "type": "boolean",
        "mutable": false,
        "complexType": {
          "original": "boolean",
          "resolved": "boolean | undefined",
          "references": {}
        },
        "required": false,
        "optional": true,
        "docs": {
          "tags": [],
          "text": "If `true`, the accordion group can have multiple\naccordion components expanded at the same time."
        },
        "attribute": "multiple",
        "reflect": false
      },
      "value": {
        "type": "string",
        "mutable": true,
        "complexType": {
          "original": "string | string[] | null",
          "resolved": "null | string | string[] | undefined",
          "references": {}
        },
        "required": false,
        "optional": true,
        "docs": {
          "tags": [],
          "text": "The value of the accordion group."
        },
        "attribute": "value",
        "reflect": false
      },
      "disabled": {
        "type": "boolean",
        "mutable": false,
        "complexType": {
          "original": "boolean",
          "resolved": "boolean",
          "references": {}
        },
        "required": false,
        "optional": false,
        "docs": {
          "tags": [],
          "text": "If `true`, the accordion group cannot be interacted with."
        },
        "attribute": "disabled",
        "reflect": false,
        "defaultValue": "false"
      },
      "readonly": {
        "type": "boolean",
        "mutable": false,
        "complexType": {
          "original": "boolean",
          "resolved": "boolean",
          "references": {}
        },
        "required": false,
        "optional": false,
        "docs": {
          "tags": [],
          "text": "If `true`, the accordion group cannot be interacted with,\nbut does not alter the opacity."
        },
        "attribute": "readonly",
        "reflect": false,
        "defaultValue": "false"
      },
      "expand": {
        "type": "string",
        "mutable": false,
        "complexType": {
          "original": "'compact' | 'inset'",
          "resolved": "\"compact\" | \"inset\"",
          "references": {}
        },
        "required": false,
        "optional": false,
        "docs": {
          "tags": [],
          "text": "Describes the expansion behavior for each accordion.\nPossible values are `\"compact\"` and `\"inset\"`.\nDefaults to `\"compact\"`."
        },
        "attribute": "expand",
        "reflect": false,
        "defaultValue": "'compact'"
      }
    };
  }
  static get events() {
    return [{
        "method": "ionChange",
        "name": "ionChange",
        "bubbles": true,
        "cancelable": true,
        "composed": true,
        "docs": {
          "tags": [],
          "text": "Emitted when the value property has changed."
        },
        "complexType": {
          "original": "AccordionGroupChangeEventDetail",
          "resolved": "AccordionGroupChangeEventDetail<any>",
          "references": {
            "AccordionGroupChangeEventDetail": {
              "location": "import",
              "path": "../../interface"
            }
          }
        }
      }];
  }
  static get methods() {
    return {
      "requestAccordionToggle": {
        "complexType": {
          "signature": "(accordionValue: string | undefined, accordionExpand: boolean) => Promise<void>",
          "parameters": [{
              "tags": [],
              "text": ""
            }, {
              "tags": [],
              "text": ""
            }],
          "references": {
            "Promise": {
              "location": "global"
            }
          },
          "return": "Promise<void>"
        },
        "docs": {
          "text": "",
          "tags": [{
              "name": "internal",
              "text": undefined
            }]
        }
      },
      "getAccordions": {
        "complexType": {
          "signature": "() => Promise<HTMLIonAccordionElement[]>",
          "parameters": [],
          "references": {
            "Promise": {
              "location": "global"
            },
            "HTMLIonAccordionElement": {
              "location": "global"
            }
          },
          "return": "Promise<HTMLIonAccordionElement[]>"
        },
        "docs": {
          "text": "",
          "tags": [{
              "name": "internal",
              "text": undefined
            }]
        }
      }
    };
  }
  static get elementRef() { return "el"; }
  static get watchers() {
    return [{
        "propName": "value",
        "methodName": "valueChanged"
      }, {
        "propName": "disabled",
        "methodName": "disabledChanged"
      }, {
        "propName": "readonly",
        "methodName": "readonlyChanged"
      }];
  }
  static get listeners() {
    return [{
        "name": "keydown",
        "method": "onKeydown",
        "target": undefined,
        "capture": false,
        "passive": false
      }];
  }
}
