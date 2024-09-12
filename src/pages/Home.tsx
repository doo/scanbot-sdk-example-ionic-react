import React from 'react';
import {
  IonContent,
  IonHeader,
  IonPage,
  IonToolbar,
  IonTitle,
  IonCard,
  IonCardHeader,
  IonCardTitle,
  IonCardContent,
} from '@ionic/react';

import { useHistory } from 'react-router';


import { CORE_FEATURES } from '../utils/data_util';
import { CoreFeatureIdEnum } from '../enums/core_feature_id_enum';

const Home: React.FC = () => {
  const history = useHistory();

  const itemOnClick = async (selectedItem: CoreFeatureIdEnum) => {
    switch (selectedItem) {
      case CoreFeatureIdEnum.DocumentDetector:
        await history.push("/document_scanner/" + selectedItem);
        break;
      case CoreFeatureIdEnum.BarcodeDetactor:
        await history.push("/barcode_scanner/" + selectedItem);
        break;
      case CoreFeatureIdEnum.DataDetactor:
        await history.push("/data_detector/" + selectedItem);
        break;
      case CoreFeatureIdEnum.Other:
        await history.push("/document_scanner/" + selectedItem);
        break;
      default:
        break;
    }
  }

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar color="primary">
          <IonTitle>Scanbot SDK Example</IonTitle>
        </IonToolbar>
      </IonHeader>

      <IonContent fullscreen>
        {
          CORE_FEATURES.map((item) => (
            <IonCard key={item.id} button onClick={() => itemOnClick(item.id)}>
              <IonCardHeader>
                <IonCardTitle>{item.title}</IonCardTitle>
              </IonCardHeader>

              <IonCardContent>{item.description}</IonCardContent>
            </IonCard>
          ))
        }
      </IonContent>
    </IonPage>
  );
};

export default Home;
