import type { ComponentInterface } from '../../stencil-public-runtime';
import type { SelectPopoverOption } from '../../interface';
/**
 * @internal
 */
export declare class SelectPopover implements ComponentInterface {
  /**
   * The header text of the popover
   */
  header?: string;
  /**
   * The subheader text of the popover
   */
  subHeader?: string;
  /**
   * The text content of the popover body
   */
  message?: string;
  /**
   * If true, the select accepts multiple values
   */
  multiple?: boolean;
  /**
   * An array of options for the popover
   */
  options: SelectPopoverOption[];
  onSelect(ev: any): void;
  private findOptionFromEvent;
  /**
   * When an option is selected we need to get the value(s)
   * of the selected option(s) and return it in the option
   * handler
   */
  private callOptionHandler;
  /**
   * This is required when selecting a radio that is already
   * selected because it will not trigger the ionChange event
   * but we still want to close the popover
   */
  private rbClick;
  private setChecked;
  private getValues;
  renderOptions(options: SelectPopoverOption[]): any;
  renderCheckboxOptions(options: SelectPopoverOption[]): any[];
  renderRadioOptions(options: SelectPopoverOption[]): any;
  render(): any;
}
