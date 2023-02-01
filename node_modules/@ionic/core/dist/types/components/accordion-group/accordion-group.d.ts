import type { ComponentInterface, EventEmitter } from '../../stencil-public-runtime';
import type { AccordionGroupChangeEventDetail } from '../../interface';
/**
 * @virtualProp {"ios" | "md"} mode - The mode determines which platform styles to use.
 */
export declare class AccordionGroup implements ComponentInterface {
  el: HTMLIonAccordionGroupElement;
  /**
   * If `true`, all accordions inside of the
   * accordion group will animate when expanding
   * or collapsing.
   */
  animated: boolean;
  /**
   * If `true`, the accordion group can have multiple
   * accordion components expanded at the same time.
   */
  multiple?: boolean;
  /**
   * The value of the accordion group.
   */
  value?: string | string[] | null;
  /**
   * If `true`, the accordion group cannot be interacted with.
   */
  disabled: boolean;
  /**
   * If `true`, the accordion group cannot be interacted with,
   * but does not alter the opacity.
   */
  readonly: boolean;
  /**
   * Describes the expansion behavior for each accordion.
   * Possible values are `"compact"` and `"inset"`.
   * Defaults to `"compact"`.
   */
  expand: 'compact' | 'inset';
  /**
   * Emitted when the value property has changed.
   */
  ionChange: EventEmitter<AccordionGroupChangeEventDetail>;
  valueChanged(): void;
  disabledChanged(): Promise<void>;
  readonlyChanged(): Promise<void>;
  onKeydown(ev: KeyboardEvent): Promise<void>;
  componentDidLoad(): Promise<void>;
  /**
   * @internal
   */
  requestAccordionToggle(accordionValue: string | undefined, accordionExpand: boolean): Promise<void>;
  private findNextAccordion;
  private findPreviousAccordion;
  /**
   * @internal
   */
  getAccordions(): Promise<HTMLIonAccordionElement[]>;
  render(): any;
}
