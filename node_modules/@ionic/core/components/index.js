/*!
 * (C) Ionic http://ionicframework.com - MIT License
 */
export { setAssetPath, setPlatformOptions } from '@stencil/core/internal/client';
export { c as createAnimation } from './animation.js';
export { iosTransitionAnimation } from './ios.transition.js';
export { mdTransitionAnimation } from './md.transition.js';
export { g as getTimeGivenProgression } from './cubic-bezier.js';
export { createGesture } from './index2.js';
export { g as getPlatforms, i as initialize, a as isPlatform } from './ionic-global.js';
import { a as addEventListener, r as raf, b as removeEventListener } from './helpers.js';
export { c as componentOnReady } from './helpers.js';
export { I as IonicSafeString } from './index3.js';
export { a as LIFECYCLE_DID_ENTER, c as LIFECYCLE_DID_LEAVE, L as LIFECYCLE_WILL_ENTER, b as LIFECYCLE_WILL_LEAVE, d as LIFECYCLE_WILL_UNLOAD } from './index4.js';
export { m as menuController } from './index5.js';
export { b as actionSheetController, a as alertController, l as loadingController, m as modalController, p as pickerController, c as popoverController, t as toastController } from './overlays.js';
export { IonAccordion, defineCustomElement as defineCustomElementIonAccordion } from './ion-accordion.js';
export { IonAccordionGroup, defineCustomElement as defineCustomElementIonAccordionGroup } from './ion-accordion-group.js';
export { IonActionSheet, defineCustomElement as defineCustomElementIonActionSheet } from './ion-action-sheet.js';
export { IonAlert, defineCustomElement as defineCustomElementIonAlert } from './ion-alert.js';
export { IonApp, defineCustomElement as defineCustomElementIonApp } from './ion-app.js';
export { IonAvatar, defineCustomElement as defineCustomElementIonAvatar } from './ion-avatar.js';
export { IonBackButton, defineCustomElement as defineCustomElementIonBackButton } from './ion-back-button.js';
export { IonBackdrop, defineCustomElement as defineCustomElementIonBackdrop } from './ion-backdrop.js';
export { IonBadge, defineCustomElement as defineCustomElementIonBadge } from './ion-badge.js';
export { IonBreadcrumb, defineCustomElement as defineCustomElementIonBreadcrumb } from './ion-breadcrumb.js';
export { IonBreadcrumbs, defineCustomElement as defineCustomElementIonBreadcrumbs } from './ion-breadcrumbs.js';
export { IonButton, defineCustomElement as defineCustomElementIonButton } from './ion-button.js';
export { IonButtons, defineCustomElement as defineCustomElementIonButtons } from './ion-buttons.js';
export { IonCard, defineCustomElement as defineCustomElementIonCard } from './ion-card.js';
export { IonCardContent, defineCustomElement as defineCustomElementIonCardContent } from './ion-card-content.js';
export { IonCardHeader, defineCustomElement as defineCustomElementIonCardHeader } from './ion-card-header.js';
export { IonCardSubtitle, defineCustomElement as defineCustomElementIonCardSubtitle } from './ion-card-subtitle.js';
export { IonCardTitle, defineCustomElement as defineCustomElementIonCardTitle } from './ion-card-title.js';
export { IonCheckbox, defineCustomElement as defineCustomElementIonCheckbox } from './ion-checkbox.js';
export { IonChip, defineCustomElement as defineCustomElementIonChip } from './ion-chip.js';
export { IonCol, defineCustomElement as defineCustomElementIonCol } from './ion-col.js';
export { IonContent, defineCustomElement as defineCustomElementIonContent } from './ion-content.js';
export { IonDatetime, defineCustomElement as defineCustomElementIonDatetime } from './ion-datetime.js';
export { IonDatetimeButton, defineCustomElement as defineCustomElementIonDatetimeButton } from './ion-datetime-button.js';
export { IonFab, defineCustomElement as defineCustomElementIonFab } from './ion-fab.js';
export { IonFabButton, defineCustomElement as defineCustomElementIonFabButton } from './ion-fab-button.js';
export { IonFabList, defineCustomElement as defineCustomElementIonFabList } from './ion-fab-list.js';
export { IonFooter, defineCustomElement as defineCustomElementIonFooter } from './ion-footer.js';
export { IonGrid, defineCustomElement as defineCustomElementIonGrid } from './ion-grid.js';
export { IonHeader, defineCustomElement as defineCustomElementIonHeader } from './ion-header.js';
export { IonIcon, defineCustomElement as defineCustomElementIonIcon } from './ion-icon.js';
export { IonImg, defineCustomElement as defineCustomElementIonImg } from './ion-img.js';
export { IonInfiniteScroll, defineCustomElement as defineCustomElementIonInfiniteScroll } from './ion-infinite-scroll.js';
export { IonInfiniteScrollContent, defineCustomElement as defineCustomElementIonInfiniteScrollContent } from './ion-infinite-scroll-content.js';
export { IonInput, defineCustomElement as defineCustomElementIonInput } from './ion-input.js';
export { IonItem, defineCustomElement as defineCustomElementIonItem } from './ion-item.js';
export { IonItemDivider, defineCustomElement as defineCustomElementIonItemDivider } from './ion-item-divider.js';
export { IonItemGroup, defineCustomElement as defineCustomElementIonItemGroup } from './ion-item-group.js';
export { IonItemOption, defineCustomElement as defineCustomElementIonItemOption } from './ion-item-option.js';
export { IonItemOptions, defineCustomElement as defineCustomElementIonItemOptions } from './ion-item-options.js';
export { IonItemSliding, defineCustomElement as defineCustomElementIonItemSliding } from './ion-item-sliding.js';
export { IonLabel, defineCustomElement as defineCustomElementIonLabel } from './ion-label.js';
export { IonList, defineCustomElement as defineCustomElementIonList } from './ion-list.js';
export { IonListHeader, defineCustomElement as defineCustomElementIonListHeader } from './ion-list-header.js';
export { IonLoading, defineCustomElement as defineCustomElementIonLoading } from './ion-loading.js';
export { IonMenu, defineCustomElement as defineCustomElementIonMenu } from './ion-menu.js';
export { IonMenuButton, defineCustomElement as defineCustomElementIonMenuButton } from './ion-menu-button.js';
export { IonMenuToggle, defineCustomElement as defineCustomElementIonMenuToggle } from './ion-menu-toggle.js';
export { IonModal, defineCustomElement as defineCustomElementIonModal } from './ion-modal.js';
export { IonNav, defineCustomElement as defineCustomElementIonNav } from './ion-nav.js';
export { IonNavLink, defineCustomElement as defineCustomElementIonNavLink } from './ion-nav-link.js';
export { IonNote, defineCustomElement as defineCustomElementIonNote } from './ion-note.js';
export { IonPicker, defineCustomElement as defineCustomElementIonPicker } from './ion-picker.js';
export { IonPickerColumn, defineCustomElement as defineCustomElementIonPickerColumn } from './ion-picker-column.js';
export { IonPickerColumnInternal, defineCustomElement as defineCustomElementIonPickerColumnInternal } from './ion-picker-column-internal.js';
export { IonPickerInternal, defineCustomElement as defineCustomElementIonPickerInternal } from './ion-picker-internal.js';
export { IonPopover, defineCustomElement as defineCustomElementIonPopover } from './ion-popover.js';
export { IonProgressBar, defineCustomElement as defineCustomElementIonProgressBar } from './ion-progress-bar.js';
export { IonRadio, defineCustomElement as defineCustomElementIonRadio } from './ion-radio.js';
export { IonRadioGroup, defineCustomElement as defineCustomElementIonRadioGroup } from './ion-radio-group.js';
export { IonRange, defineCustomElement as defineCustomElementIonRange } from './ion-range.js';
export { IonRefresher, defineCustomElement as defineCustomElementIonRefresher } from './ion-refresher.js';
export { IonRefresherContent, defineCustomElement as defineCustomElementIonRefresherContent } from './ion-refresher-content.js';
export { IonReorder, defineCustomElement as defineCustomElementIonReorder } from './ion-reorder.js';
export { IonReorderGroup, defineCustomElement as defineCustomElementIonReorderGroup } from './ion-reorder-group.js';
export { IonRippleEffect, defineCustomElement as defineCustomElementIonRippleEffect } from './ion-ripple-effect.js';
export { IonRoute, defineCustomElement as defineCustomElementIonRoute } from './ion-route.js';
export { IonRouteRedirect, defineCustomElement as defineCustomElementIonRouteRedirect } from './ion-route-redirect.js';
export { IonRouter, defineCustomElement as defineCustomElementIonRouter } from './ion-router.js';
export { IonRouterLink, defineCustomElement as defineCustomElementIonRouterLink } from './ion-router-link.js';
export { IonRouterOutlet, defineCustomElement as defineCustomElementIonRouterOutlet } from './ion-router-outlet.js';
export { IonRow, defineCustomElement as defineCustomElementIonRow } from './ion-row.js';
export { IonSearchbar, defineCustomElement as defineCustomElementIonSearchbar } from './ion-searchbar.js';
export { IonSegment, defineCustomElement as defineCustomElementIonSegment } from './ion-segment.js';
export { IonSegmentButton, defineCustomElement as defineCustomElementIonSegmentButton } from './ion-segment-button.js';
export { IonSelect, defineCustomElement as defineCustomElementIonSelect } from './ion-select.js';
export { IonSelectOption, defineCustomElement as defineCustomElementIonSelectOption } from './ion-select-option.js';
export { IonSelectPopover, defineCustomElement as defineCustomElementIonSelectPopover } from './ion-select-popover.js';
export { IonSkeletonText, defineCustomElement as defineCustomElementIonSkeletonText } from './ion-skeleton-text.js';
export { IonSlide, defineCustomElement as defineCustomElementIonSlide } from './ion-slide.js';
export { IonSlides, defineCustomElement as defineCustomElementIonSlides } from './ion-slides.js';
export { IonSpinner, defineCustomElement as defineCustomElementIonSpinner } from './ion-spinner.js';
export { IonSplitPane, defineCustomElement as defineCustomElementIonSplitPane } from './ion-split-pane.js';
export { IonTab, defineCustomElement as defineCustomElementIonTab } from './ion-tab.js';
export { IonTabBar, defineCustomElement as defineCustomElementIonTabBar } from './ion-tab-bar.js';
export { IonTabButton, defineCustomElement as defineCustomElementIonTabButton } from './ion-tab-button.js';
export { IonTabs, defineCustomElement as defineCustomElementIonTabs } from './ion-tabs.js';
export { IonText, defineCustomElement as defineCustomElementIonText } from './ion-text.js';
export { IonTextarea, defineCustomElement as defineCustomElementIonTextarea } from './ion-textarea.js';
export { IonThumbnail, defineCustomElement as defineCustomElementIonThumbnail } from './ion-thumbnail.js';
export { IonTitle, defineCustomElement as defineCustomElementIonTitle } from './ion-title.js';
export { IonToast, defineCustomElement as defineCustomElementIonToast } from './ion-toast.js';
export { IonToggle, defineCustomElement as defineCustomElementIonToggle } from './ion-toggle.js';
export { IonToolbar, defineCustomElement as defineCustomElementIonToolbar } from './ion-toolbar.js';
export { IonVirtualScroll, defineCustomElement as defineCustomElementIonVirtualScroll } from './ion-virtual-scroll.js';

const setupConfig = (config) => {
  const win = window;
  const Ionic = win.Ionic;
  // eslint-disable-next-line @typescript-eslint/prefer-optional-chain
  if (Ionic && Ionic.config && Ionic.config.constructor.name !== 'Object') {
    return;
  }
  win.Ionic = win.Ionic || {};
  win.Ionic.config = Object.assign(Object.assign({}, win.Ionic.config), config);
  return win.Ionic.config;
};
const getMode = () => {
  var _a;
  const win = window;
  const config = (_a = win === null || win === void 0 ? void 0 : win.Ionic) === null || _a === void 0 ? void 0 : _a.config;
  if (config) {
    if (config.mode) {
      return config.mode;
    }
    else {
      return config.get('mode');
    }
  }
  return 'md';
};

/**
 * This is a plugin for Swiper that allows it to work
 * with Ionic Framework and the routing integrations.
 * Without this plugin, Swiper would be incapable of correctly
 * determining the dimensions of the slides component as
 * each view is initially hidden before transitioning in.
 */
const setupSwiperInIonic = (swiper, watchForIonPageChanges = true) => {
  if (typeof window === 'undefined') {
    return;
  }
  const swiperEl = swiper.el;
  const ionPage = swiperEl.closest('.ion-page');
  if (!ionPage) {
    if (watchForIonPageChanges) {
      /**
       * If no ion page found, it is possible
       * that we are in the overlay setup step
       * where the inner component has been
       * created but not attached to the DOM yet.
       * If so, wait for the .ion-page class to
       * appear on the root div and re-run setup.
       */
      const rootNode = swiperEl.getRootNode();
      if (rootNode.tagName === 'DIV') {
        const mo = new MutationObserver((m) => {
          const mutation = m[0];
          const wasEmpty = mutation.oldValue === null;
          const hasIonPage = rootNode.classList.contains('ion-page');
          /**
           * Now that we have an .ion-page class
           * we can safely attempt setup again.
           */
          if (wasEmpty && hasIonPage) {
            mo.disconnect();
            /**
             * Set false here so we do not
             * get infinite loops
             */
            setupSwiperInIonic(swiper, false);
          }
        });
        mo.observe(rootNode, {
          attributeFilter: ['class'],
          attributeOldValue: true,
        });
      }
    }
    return;
  }
  /**
   * If using slides in a modal or
   * popover we need to wait for the
   * overlay to be shown as these components
   * are hidden when they are initially created.
   */
  const modalOrPopover = swiperEl.closest('ion-modal, ion-popover');
  if (modalOrPopover) {
    const eventName = modalOrPopover.tagName === 'ION-MODAL' ? 'ionModalWillPresent' : 'ionPopoverWillPresent';
    const overlayCallback = () => {
      /**
       * We need an raf here so the update
       * is fired one tick after the overlay is shown.
       */
      raf(() => {
        swiperEl.swiper.update();
        removeEventListener(modalOrPopover, eventName, overlayCallback);
      });
    };
    addEventListener(modalOrPopover, eventName, overlayCallback);
  }
  else {
    /**
     * If using slides in a page
     * we need to wait for the ion-page-invisible
     * class to be removed so Swiper can correctly
     * compute the dimensions of the slides.
     */
    const mo = new MutationObserver((m) => {
      var _a;
      const mutation = m[0];
      const wasPageHidden = (_a = mutation.oldValue) === null || _a === void 0 ? void 0 : _a.includes('ion-page-invisible');
      const isPageHidden = ionPage.classList.contains('ion-page-invisible');
      /**
       * Only update Swiper if the page was
       * hidden but is no longer hidden.
       */
      if (!isPageHidden && isPageHidden !== wasPageHidden) {
        swiperEl.swiper.update();
      }
    });
    mo.observe(ionPage, {
      attributeFilter: ['class'],
      attributeOldValue: true,
    });
  }
  /**
   * We also need to listen for the appload event
   * which is emitted by Stencil in the
   * event that Swiper is being used on the
   * view that is rendered initially.
   */
  const onAppLoad = () => {
    swiperEl.swiper.update();
    removeEventListener(window, 'appload', onAppLoad);
  };
  addEventListener(window, 'appload', onAppLoad);
};
const IonicSwiper = {
  name: 'ionic',
  on: {
    afterInit(swiper) {
      console.warn('[Deprecation Warning]: The IonicSwiper module has been deprecated in favor of the IonSlides module. This change was made to better support the Swiper 7 release. The IonicSwiper module will be removed in Ionic 7.0. See https://ionicframework.com/docs/api/slides#migration for revised migration steps.');
      setupSwiperInIonic(swiper);
    },
  },
};

const IonicSlides = (opts) => {
  const { swiper, extendParams } = opts;
  const slidesParams = {
    effect: undefined,
    direction: 'horizontal',
    initialSlide: 0,
    loop: false,
    parallax: false,
    slidesPerView: 1,
    spaceBetween: 0,
    speed: 300,
    slidesPerColumn: 1,
    slidesPerColumnFill: 'column',
    slidesPerGroup: 1,
    centeredSlides: false,
    slidesOffsetBefore: 0,
    slidesOffsetAfter: 0,
    touchEventsTarget: 'container',
    autoplay: false,
    freeMode: false,
    freeModeMomentum: true,
    freeModeMomentumRatio: 1,
    freeModeMomentumBounce: true,
    freeModeMomentumBounceRatio: 1,
    freeModeMomentumVelocityRatio: 1,
    freeModeSticky: false,
    freeModeMinimumVelocity: 0.02,
    autoHeight: false,
    setWrapperSize: false,
    zoom: {
      maxRatio: 3,
      minRatio: 1,
      toggle: false,
    },
    touchRatio: 1,
    touchAngle: 45,
    simulateTouch: true,
    touchStartPreventDefault: false,
    shortSwipes: true,
    longSwipes: true,
    longSwipesRatio: 0.5,
    longSwipesMs: 300,
    followFinger: true,
    threshold: 0,
    touchMoveStopPropagation: true,
    touchReleaseOnEdges: false,
    iOSEdgeSwipeDetection: false,
    iOSEdgeSwipeThreshold: 20,
    resistance: true,
    resistanceRatio: 0.85,
    watchSlidesProgress: false,
    watchSlidesVisibility: false,
    preventClicks: true,
    preventClicksPropagation: true,
    slideToClickedSlide: false,
    loopAdditionalSlides: 0,
    noSwiping: true,
    runCallbacksOnInit: true,
    coverflowEffect: {
      rotate: 50,
      stretch: 0,
      depth: 100,
      modifier: 1,
      slideShadows: true,
    },
    flipEffect: {
      slideShadows: true,
      limitRotation: true,
    },
    cubeEffect: {
      slideShadows: true,
      shadow: true,
      shadowOffset: 20,
      shadowScale: 0.94,
    },
    fadeEffect: {
      crossFade: false,
    },
    a11y: {
      prevSlideMessage: 'Previous slide',
      nextSlideMessage: 'Next slide',
      firstSlideMessage: 'This is the first slide',
      lastSlideMessage: 'This is the last slide',
    },
  };
  if (swiper.pagination) {
    slidesParams.pagination = {
      type: 'bullets',
      clickable: false,
      hideOnClick: false,
    };
  }
  if (swiper.scrollbar) {
    slidesParams.scrollbar = {
      hide: true,
    };
  }
  extendParams(slidesParams);
};

export { IonicSlides, IonicSwiper, getMode, setupConfig };
